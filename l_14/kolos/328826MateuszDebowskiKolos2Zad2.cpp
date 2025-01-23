#include <iostream>
#include <vector>

template <typename T> 

class Sorter{
private:
    std::vector v;
public:
    Sorter(std::vector<T>& _v) : v(_v){}
    virtual ~Sorter(){}
    virtual void sort(bool descending) = 0;
};

template <typename T>

class Algorytm : public Sorter<T> {
public:
    Algorytm(){}

    virtual void sort(bool descending) const override{}
};

int main(){
    std::vector<double> v{5.2, -5.1, 6, 10.001, 1111};
    auto s = YourSorter(v);
    s.sort(true);
    // wartosci wektora
    s.sort(false);
    // wartosci wektora

    return 0;
}