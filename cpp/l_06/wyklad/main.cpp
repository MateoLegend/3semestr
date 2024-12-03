#include <iostream>

class Car {
public:
    Car(const std::string &_man, const std::string &_mod, const std::string &_vin)
        : manufacturer(_man), model(_mod), vin(_vin){}
    void drive(){std::cout << "Drive " << vin <<"\n";}
    void setVin(const std::string &_vin) { this->vin = _vin;}
protected:
    Car(){};
private:
    std::string manufacturer;
    std::string model;
    std::string vin;
};

class PetrolCar : virtual public Car {
public:
    PetrolCar(const std::string &_man, const std::string &_mod, const std::string &_vin)
        : Car(_man, _mod, _vin){}
protected:
    PetrolCar(){};
};

class ElectricCar : virtual public Car {
public:
    ElectricCar(const std::string &_man, const std::string &_mod, const std::string &_vin)
        : Car(_man, _mod, _vin){}
protected:
    ElectricCar(){};
};

class HybridCar : public PetrolCar, public ElectricCar {
public:
    HybridCar(const std::string &_man, const std::string &_mod, const std::string &_vin)
        : PetrolCar(), ElectricCar(), Car(_man, _mod, _vin) {}
};

int main(){
    HybridCar hc("Manuf","Model","121212");
    PetrolCar &pc = static_cast<PetrolCar&>(hc);
    ElectricCar &ec = static_cast<ElectricCar&>(hc);
    pc.drive();
    ec.drive();

    pc.setVin("123123");
    ec.setVin("333123");

    pc.drive();
    ec.drive();
    return 0;
}