#include <typeinfo>
#include <iostream>

template<typename T>

void f(T val){
    std::cout << typeid(T).name() << ": " << val << '\n';
}



int main(){
    int i = 0;
    double j = 1.0;
    f<int>(i);
    f<double>(j);

    return 0;
}