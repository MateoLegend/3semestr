#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


class Process{
protected:
    std::string name;
    int length;
    int start;

public:
    Process(std::string name, int length, int start)
        : name(name), length(length), start(start) {}

    void run(int time){
        length -= time;
    }

    void print() const{
        std::cout << name << " (length=" << length << ")";
    }

    bool isFinished(){
        return length == 0;
    }
};

class RoundRobinScheduler{
private:

public:
    RoundRobinScheduler(){}

    void loadProcesses(const std::string& filename){
        std::ifstream file(filename);   // biblioteka fstream
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line); // biblioteka sstream
            std::string name;
            int length, start;

            std::getline(ss, name, ',');
            ss >> length;
            ss.ignore(1, ',');
            ss >> start;
        }
    }
};



int main(int argc, char* argv[]){
    

    return 0;
}