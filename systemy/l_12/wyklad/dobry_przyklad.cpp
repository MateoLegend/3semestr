#include <thread>
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <string>
#include <unistd.h>

std::mutex mutex;
std::condition_variable cv;

std::string sharedString;
bool flag = false;

void threadFunc(){
    std::cout << "wątek oczekuje na zmianę flagi\n";
    {
        std::unique_lock lock(mutex); /* automatyczny lock() na mutex */
        cv.wait(lock, []{return flag; });
        /* kontynuujemy wykonanie, gdy flaga zostanie zmieniana na true */

        std::cout << "wątek zaczyna działanie\n";
        std::cout << sharedString << std::endl;
        sharedString = "kot ma ale\n";

        /* mutex unlock w destruktorze unique_lock */
    }
}


int main(){
    std::thread t(threadFunc);
    sleep(2);

    {
        std::lock_guard lock(mutex); /* mutex lock */
        sharedString = "zmiana w main()\n";
        flag = true;
        cv.notify_one();
        /* mutex unlock w destruktorze lock_guard */
    }

    // sharedString = "ala ma kota";
    // std::cout << "wątek zmienia flagę\n";
    // flag = true;
    
    // while(flag);
    // std::cout << sharedString << std::endl;
    
    t.join();
    return 0;
}