#include <iostream>
#include <algorithm>
#include <unordered_map>

bool isAnagram(const std::string& first, const std::string& second){
    if(first.size() != second.size()){
        std::cout << "Różna długość słów." << std::endl;
        return false;
    }
    std::unordered_map<char, int> freqMapFirst, freqMapSecond;
    for(char c : first){
        freqMapFirst[c] += 1;
        std::cout << c << std::endl;
    }
    for(char c : second){
        freqMapSecond[c] += 1;
        std::cout << c << std::endl;
    }

    return true;
}

int main(){
    isAnagram("Mama", "Mama");
    return 0;
}
