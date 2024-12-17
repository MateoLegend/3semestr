#include <iostream>
#include <thread>
#include <vector>
#include <cmath>



class IfPrime
{
public:
    IfPrime(unsigned int threads)
    {
        this->threads = threads;
        this->isPrime = true;
    }

    bool check(unsigned int n) {
        /* Uruchamiamy wątki */
        std::vector<std::thread> threads;

        const unsigned int limit = sqrt(n);
        std::cout << "Up to: " << limit << std::endl;
        unsigned int range = limit / this->threads;

        for (int i = 0; i < this->threads; i++)
        {
            if (n == 1) return false;

            unsigned int from = i*range;
            if (from == 0)
                from = 2;
            unsigned int to = (i == this->threads - 1) ?  limit : (i+1)*range;
            std::cout << from << " " << to << std::endl;
            threads.push_back(std::thread(&IfPrime::threadFunction, this, from, to, n));
        }

        for (int i = 0; i < this->threads; i++)
        {
            threads[i].join();
        }

        return this->isPrime;
    }

private:
    void threadFunction(unsigned int from, unsigned int to, unsigned int n) {
        for (unsigned int i = from; i <= to; i++)
        {
            if (n % i == 0)
                this->isPrime = false;

        }
    }

    unsigned int threads;
    volatile bool isPrime;
};

int main() {
    unsigned int hwThreads = std::thread::hardware_concurrency();
    hwThreads = hwThreads ? hwThreads : 1;
    IfPrime p(hwThreads);

    unsigned int n = 4;
    if (p.check(n))  {
        std::cout << "Liczba " << n << " jest pierwsza" << std::endl;
    } else {
        std::cout << "Liczba " << n << " nie jest pierwsza" << std::endl;
    }

    return 0;
}