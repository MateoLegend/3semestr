#include <iostream>
#include <stdexcept>

template <typename T> 
class Shape{
public:
    virtual ~Shape() = default;
    virtual T area() const = 0;
};

template <typename T>

class Rectangle : public Shape<T>{
private:
    T width, height;
public:
    Rectangle(const T _width, const T _height) : width(_width), height(_height){
        if(width <= 0 || height <= 0){
            throw std::invalid_argument("Należy wpisać wartość większą niż zero dla długości lub wysokości figury.");
        }
    }
    virtual T area() const override{
        return width * height;
    }
};

template <typename T>
class Square : public Rectangle<T>{
private:
    T bok;
public:
    Square(const T _bok) :Rectangle<T>(_bok, _bok){
        if(bok <= 0){
            throw std::invalid_argument("Należy wpisać wartość większą niż zero dla długości boku kwadratu.");
        }
    }

};

int main(){
    try{
        Rectangle<int> prostokat1(2, 3);
        Square<int> kwadrat1(2);

        Rectangle<double> prostokat2(2.5, 3.5);
        Square<double> kwadrat2(2.5);

        std::cout << "Pole Prostokąta int: " << prostokat1.area() << std::endl;
        std::cout << "Pole Prostokąta double: " << prostokat2.area() << std::endl;
        std::cout << "Pole Kwadratu int: " << kwadrat1.area() << std::endl;
        std::cout << "Pole Kwadratu double: " << kwadrat2.area() << std::endl;

        try{
            Rectangle<int> invalidProstokat1(-1, 1);
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
        try{
            Square<int> invalidKwadrat1(-2);
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }
    catch(const std::exception& e){
        std::cerr << "Błąd: " << e.what() << std::endl;
    }
}