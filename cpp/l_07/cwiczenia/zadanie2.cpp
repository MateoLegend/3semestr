#include <iostream>

class ICommand{
public:
    ICommand(){
        std::cout << "Konstruktor klasy ICommand" << std::endl;
    }
    virtual ~ICommand(){
        std::cout << "Destruktor klasy ICommand" << std::endl;
    }

    virtual char getCommand() const = 0;
};

class SystemUptime : public ICommand{
public:
    SystemUptime(){
        std::cout << "Konstruktor klasy SystemUptime" << std::endl;
    }
    ~SystemUptime(){
        std::cout << "Destruktor klasy SystemUptime" << std::endl;
    }

    char getCommand() const override {
        return 'U';     // ma znaczenie jakich ciapek użyjemy
    }
};

class SystemMemory : public ICommand{
public:
    SystemMemory(){
        std::cout << "Konstruktor klasy SystemMemory" << std::endl;
    }
    ~SystemMemory(){
        std::cout << "destruktor klasy SystemMemory" << std::endl;
    }

    char getCommand() const override {
        return 'M';
    }
};

void printCommand(const ICommand *c){
    std::cout << c->getCommand() << std::endl;
}


int main(){
    ICommand *su = new SystemUptime;
    ICommand *sm = new SystemMemory;

    printCommand(su);
    printCommand(sm);

    delete su;
    delete sm;

    return 0;
}