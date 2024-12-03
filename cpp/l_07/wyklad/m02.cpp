#include <iostream>
#include <typeinfo>

template <typename T, size_t n>
template <class T, size_t n>

class Array{
public:
    Array(){};
    Array(T value){
        for(size_t i = 0; i < n; i++){
            buffer[i] = value;
        }
    }

    T& operator[](std::size_t idx){
        static T fallback = 0;
        return (idx >= n) ? fallback : buffer[idx];
    }

    const T& operator[](std::size_t idx) const {
        static T fallback = 0;
        return (idx >= n) ? fallback : buffer[idx];
    }


private:
    T buffer[n];
};


int main(){
    Array<int, 2> arr(123);
    std::cout << arr[10000] << std::endl;

    return 0;
}