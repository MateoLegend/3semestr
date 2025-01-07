#include <thread>
#include <iostream>
#include <string>
#include <unistd.h>

std::string sharedString;
bool flag = false;

void threadFunc(){
    std::cout << "wątek oczekuje na zmianę flagi\n";
    while(!flag);
    sleep(1);
    std::cout << "wątek zaczyna działanie\n";
    std::cout << sharedString << std::endl;
    sharedString = "kot ma ale";

    flag = false;
}


int main(){
    std::thread t(threadFunc);
    sleep(2);

    sharedString = "ala ma kota";
    std::cout << "wątek zmienia flagę\n";
    flag = true;
    
    while(flag);
    std::cout << sharedString << std::endl;
    
    t.join();
    return 0;
}