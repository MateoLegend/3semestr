#include <iostream>

class ICommand{
private:
    char text;

public:
    ICommand(char _text) : text(_text){}
    ~ICommand(){}

    virtual char getCommand() = 0;

    char getCommand(const char text){
        return text;
    }
};


class SystemUptime : ICommand {
public:
    SystemUptime(char _text) : ICommand(_text) {
        std::cout << "Wykonanie konstruktora klasy SystemUptime:\n" << std::endl;
    }
    ~SystemUptime(){
        std::cout << "Wykonanie destruktora klasy SystemUptime.\n" << std::endl;
    }

    char getCommand(){
        text = "U";
        return text;
    }
protected:
    SystemUptime(){};
};


class SystemMemory : ICommand {
public:
    SystemMemory(char _text) : ICommand(_text){
        std::cout << "Wykonanie konstruktora klasy SystemMemory:\n" << std::endl;
    }
    ~SystemMemory(){
        std::cout << "Wykonanie destruktora klasy SystemMemory.\n" << std::endl;
    }
    char getCommand(){
        text = "M";
        return text;
    }
protected:
    SystemMemory(){};
};


void printCommand(const ICommand *c){
   std::cout << c->getCommand() << std::endl;
}


int main(){
    SystemUptime(20);
    SystemMemory(20);
    return 0;
}