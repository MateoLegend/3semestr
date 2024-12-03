#include <iostream>

class Complex {
public:
    Complex(double _re, double _im){
        re = _re;
        im = _im;
    }
    Complex(double _re){
        re = _re;
        im = 0;
    }
    
    // zwrócenie liczb z private

    double real() const{
        return re;
    }

    double imag() const{
        return im;
    }

    // operatory przeciążenia
    
    Complex operator+(const Complex &c){    // Complex + Complex
        return Complex(re + c.re, im + c.im);
    }

    Complex operator-(const Complex &c){    // Complex - Complex
        return Complex(re - c.re, im - c.im);
    }
    Complex& operator+=(const Complex &c){  // Complex += Complex
        re = re + c.re;
        im = im + c.im;
        return *this;
    }
    Complex& operator-=(const Complex &c){  // Complex -= Complex
        re = re - c.re;
        im = im - c.im;
        return *this;        
    }
    Complex operator*(double x){            // Complex * double
        return Complex(re * 2, im * 2);
    }
    Complex operator-(){                    // -Complex [operator unarny (jednoargumentowy)]
        return Complex(-re, -im);
    }


private:
    double re;
    double im;
};
std::ostream& operator<<(std::ostream &os, const Complex &c){
    os << c.real() << "+" << "i" << std::endl;
    return os;
}


int main(){
    Complex a(1.0, 2.0);
    Complex b(2.0, 1.0);
    Complex c(a + b);

    std::cout << c;

    return 0;
}