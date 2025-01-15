#include <iostream>
#include <cmath>

template <typename T>

class Vector {
public:
    virtual ~Vector(){}
    virtual double length() const = 0;
    virtual void normalize() = 0;
};


template <typename T>
class Vector2D : Vector<T>{
protected:
    T x, y;
public:
    Vector2D(const T _x, const T _y): x(_x), y(_y){}
    ~Vector2D(){}

    virtual double length() const override{
        // return hypot(x, y);
        return sqrt(x*x + y*y);
    }

    virtual void normalize() override{
        double len = length();
        this->x /= len;
        this->y /= len;
        std::cout << "Normalizacja: x: " << x << ", y: " << y << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")\n";
        return os;
    }
};


template <typename T>
class Vector3D : Vector2D<T>{
protected:
    T z;
public:
    Vector3D(const T _x, const T _y, const T _z): Vector2D<T>(_x, _y), z(_z){}
    ~Vector3D(){}

    virtual double length() const override{
        return sqrt(this->x*this->x + this->y*this->y + z*z);
    }


    virtual void normalize() override {
        double len = length();
        this->x /= len;
        this->y /= len;
        this->z /= len;
        std::cout << "Normalizacja: x: " << this->x << ", y: " << this->y << ", z: " << z << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
        return os;
    }
};


int main(){
    Vector2D<double> v2d(3,4);
    std::cout << v2d.length() << std:: endl;
    std::cout << v2d << std:: endl;
    v2d.normalize();
    std::cout << v2d << std:: endl;

    return 0;
}
