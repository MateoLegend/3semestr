#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>

class Process {
public:
    std::string name;  // Nazwa procesu
    int length;        // Długość procesu (czas trwania)
    int start;         // Czas rozpoczęcia procesu

    Process(std::string name, int length, int start)
        : name(name), length(length), start(start) {}

    // Zmniejsza czas trwania procesu o daną liczbę jednostek czasu
    void run(int time) {
        length -= time;
        if (length < 0) length = 0;
    }

    bool isFinished() const {
        return length == 0;
    }

    void print() const {
        std::cout << name << " (length=" << length << ")";
    }
};

class RoundRobinScheduler {
private:
    std::queue<Process*> readyQueue;    // Kolejka gotowych procesów
    std::vector<Process*> allProcesses; // Wszyscy procesy
    int quantum;                        // Długość kwantu czasu
    int currentTime;                    // Aktualny czas w systemie

public:
    RoundRobinScheduler(int quantum) : quantum(quantum), currentTime(0) {}

    // Wczytanie procesów z pliku
    void loadProcesses(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name;
            int length, start;

            std::getline(ss, name, ',');
            ss >> length;
            ss.ignore(1, ','); // Ignorujemy przecinek
            ss >> start;

            Process* process = new Process(name, length, start);
            allProcesses.push_back(process);
        }
    }

    // Uruchomienie algorytmu Round Robin
    void run() {
        while (true) {
            // Dodaj procesy, które powinny zacząć działać w danym momencie
            for (auto& process : allProcesses) {
                if (process->start == currentTime) {
                    std::cout << "T=" << currentTime << ": New process ";
                    process->print();
                    std::cout << " is waiting for execution\n";
                    readyQueue.push(process);
                }
            }

            // Jeśli kolejka procesów gotowych jest pusta, kończymy działanie
            if (readyQueue.empty()) {
                std::cout << "T=" << currentTime << ": No processes currently available\n";
                break;
            }

            // Wybieramy proces z kolejki gotowych do uruchomienia
            Process* currentProcess = readyQueue.front();
            readyQueue.pop();

            // Uruchamiamy proces przez kwant czasu lub do jego zakończenia
            int runTime = std::min(quantum, currentProcess->length);
            std::cout << "T=" << currentTime << ": " << "P" << currentProcess->name
                      << " will be running for " << runTime << " time units. Time left: "
                      << (currentProcess->length - runTime) << "\n";

            // Zmniejszamy czas procesu o liczbę jednostek czasu, które zostały wykonane
            currentProcess->run(runTime);
            currentTime += runTime;

            // Jeśli proces nie skończył się, wrzucamy go z powrotem do kolejki
            if (!currentProcess->isFinished()) {
                readyQueue.push(currentProcess);
            } else {
                std::cout << "T=" << currentTime << " " << "Process P" << currentProcess->name
                          << " has been finished\n";
            }
        }

        std::cout << "T=" << currentTime << ": No more processes in queues\n";
    }
};


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./rr <filename.csv> <quantum>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int quantum = std::stoi(argv[2]);

    RoundRobinScheduler scheduler(quantum);
    scheduler.loadProcesses(filename);
    scheduler.run();

    return 0;
}
