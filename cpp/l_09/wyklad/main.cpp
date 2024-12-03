// napisz funkcje ktora zwroci element ktory najczesciej sie powtarza wraz z liczba jego powtorzen

#include <iostream>
#include <vector>
#include <utility>
#include <map>

template <typename T>
std::pair<T, unsigned int>

findMostOccurrences(std::vector<T> &v){
    if(v.empty()){
        throw std::length_error("Vector is empty.");
    }

    /*Implementacja klasy std::map zapewnia inicjalizacje wartości, które nie istnieją w przypadku odwołania przez [] */
    std::map<T, size_t> map;

    for(const auto &value : v){
        map[value] += 1;
    }

    // for(std::pair<T, size_t> &value : map)
    std::pair<int, unsigned int> result;
    result.second = 0;

    for(const auto &value : map){
        
        if(value.second > result.second){
            result.first = value.first;
            result.second = value.second;
        }
        //std::cout << value.first << " " << value.second << std::endl;
    }
    
    return result;
}

int main(){
    std::vector<int> numbers = {1,2,3,4,5,6,6,7,1,1,2,3,4,5,6,1,2,3,4,5,6,7,8,9,0,6,8,4,5};
    
    std::pair<int, unsigned int> result = findMostOccurrences<int>(numbers);
    std::cout << "Najczęściej występuje: " << result.first << std::endl;
    std::cout << "Występuje " << result.first << " razy." << std::endl;
    return 0;
}