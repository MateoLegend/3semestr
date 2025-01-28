#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>

class BuddyAllocator {
private:
    size_t memory_size;
    size_t max_splits;
    std::map<size_t, std::vector<size_t>> free_blocks; // rozmiar bloku -> lista adresów początkowych

public:
    BuddyAllocator(size_t memory_size, size_t max_splits) : memory_size(memory_size), max_splits(max_splits) {
        if ((memory_size & (memory_size - 1)) != 0) {
            throw std::invalid_argument("Rozmiar pamięci musi być potęgą 2.");
        }

        size_t min_block_size = memory_size >> max_splits;
        if (min_block_size < 1) {
            throw std::invalid_argument("Zbyt wiele podziałów dla danego rozmiaru pamięci.");
        }

        free_blocks[memory_size].push_back(0); // Rozpocznij z jednym wolnym blokiem pełnego rozmiaru pamięci
    }

    std::pair<size_t, size_t> alloc(size_t size) {
        size_t block_size = 1;
        while (block_size < size) {
            block_size <<= 1;
        }

        if (block_size > memory_size || block_size < (memory_size >> max_splits)) {
            throw std::invalid_argument("Żądany rozmiar wykracza poza dopuszczalny zakres bloków.");
        }

        size_t current_block_size = block_size;
        while (free_blocks[current_block_size].empty() && current_block_size < memory_size) {
            current_block_size <<= 1;
        }

        if (current_block_size > memory_size) {
            throw std::runtime_error("Brak dostępnego odpowiedniego bloku.");
        }

        while (current_block_size > block_size) {
            size_t block_address = free_blocks[current_block_size].back();
            free_blocks[current_block_size].pop_back();
            current_block_size >>= 1;

            free_blocks[current_block_size].push_back(block_address);
            free_blocks[current_block_size].push_back(block_address + current_block_size);
        }

        size_t allocated_address = free_blocks[block_size].back();
        free_blocks[block_size].pop_back();

        return {allocated_address, block_size};
    }

    void free(size_t address, size_t size) {
        if ((size & (size - 1)) != 0 || size > memory_size || size < (memory_size >> max_splits)) {
            throw std::invalid_argument("Niepoprawny rozmiar bloku.");
        }

        size_t buddy_address = address ^ size;
        auto &blocks = free_blocks[size];

        auto it = std::find(blocks.begin(), blocks.end(), buddy_address);
        if (it != blocks.end()) {
            blocks.erase(it);
            free(address < buddy_address ? address : buddy_address, size << 1);
        } else {
            blocks.push_back(address);
        }
    }

    void print_free_blocks() {
        std::cout << "Wolne bloki:\n";
        for (const auto &[block_size, addresses] : free_blocks) {
            if (!addresses.empty()) {
                std::cout << "Rozmiar bloku " << block_size << ": ";
                for (size_t addr : addresses) {
                    std::cout << addr << " ";
                }
                std::cout << "\n";
            }
        }
    }
};

int main() {
    try {
        BuddyAllocator allocator(1024, 5);

        auto block1 = allocator.alloc(128);
        std::cout << "Przydzielony blok pod adresem " << block1.first << " z rozmiarem " << block1.second << "\n";

        auto block2 = allocator.alloc(64);
        std::cout << "Przydzielony blok pod adresem " << block2.first << " z rozmiarem " << block2.second << "\n";

        allocator.free(block1.first, block1.second);
        std::cout << "Zwolniony blok pod adresem " << block1.first << "\n";

        allocator.print_free_blocks();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}