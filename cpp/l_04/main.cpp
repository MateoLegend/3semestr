#include <iostream>
#include <cstring>

class Computer {
private:
    std::string manufacturer;
    std::string model;
    std::string cpu;
    unsigned int ramMemory;     //GB
    unsigned int diskMemory;    //GB

public:
    Computer(const std::string& _manufacturer,const std::string& _model,const std::string& _cpu, unsigned int _ramMemory, unsigned int _diskMemory)
        : manufacturer(_manufacturer), model(_model), cpu(_cpu), ramMemory(_ramMemory), diskMemory(_diskMemory) {};

    void print() const{
        std::cout << manufacturer << ", " << model << ", " << cpu << ", " << ramMemory << "GB RAM, " << diskMemory << "GB DISK " << std::endl;
    }

    void setManufacturer(const std::string& manufacturer){
        this->manufacturer = manufacturer;
    }

    void setModel(const std::string& model){
        this->model = model;
    }

    void setCpu(const std::string& cpu){
        this->cpu = cpu;
    }

    void setRamMemory(unsigned int ramMemory){
        this->ramMemory = ramMemory;
    }

    void setDiskMemory(unsigned int diskMemory){
        this->diskMemory = diskMemory;
    }
};

class Laptop : Computer{
private:
    unsigned int screen;    //inches
    unsigned int battery;   //Wh

public:
    Laptop(const std::string& _manufacturer,const std::string& _model,const std::string& _cpu, unsigned int _ramMemory,
    unsigned int _diskMemory, unsigned int _screen, unsigned int _battery)
    : Computer(_manufacturer, _model, _cpu, _ramMemory, _diskMemory) , screen(_screen), battery(_battery) {};

    Laptop(const Computer &_c, unsigned int _screen, unsigned int _battery): Computer(_c), screen(_screen), battery(_battery) {};

    void print() const{
        std::cout << screen << " inches, " << battery << " Wh" << std::endl; 
    }
};

class Desktop : Computer{
protected:
    std::string formFactor;
    std::string psu;

public:
    Desktop(const std::string& _manufacturer,const std::string& _model,const std::string& _cpu, unsigned int _ramMemory,
    unsigned int _diskMemory, const std::string& _formFactor, const std::string& _psu)
    : Computer(_manufacturer, _model, _cpu, _ramMemory, _diskMemory), formFactor(_formFactor), psu(_psu) {};

    void print()const {
        std::cout << formFactor << " / " << psu << std::endl;
    }

};


int main(){
    Computer computer("SNSV", "Longtitude 555", "i11", 16, 512);
    computer.print();
    Laptop laptop("SNSV", "Longtitude 555", "i11", 16, 512, 14, 50);
    laptop.print();
    Laptop laptop2(computer, 15, 48);
    laptop2.print();
    Desktop desktop("SNSV", "Longtitude 555", "i11", 16, 512, "SFF", "550W 80 Plus Gold");
    desktop.print();

    return 0;
}