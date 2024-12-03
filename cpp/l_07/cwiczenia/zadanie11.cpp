#include <iostream>
#include <cstdlib>
#include <string.h>


class TimeLength{
public:
    TimeLength(const char* _seconds): copy(strdup(_seconds)) {}
    ~TimeLength(){
        delete [] copy;
    }

    // konstruktor kopiujący
    TimeLength(const TimeLength &source){
        copy = source.copy;
    }


    TimeLength& operator<<(const TimeLength &source){
        free(copy);
        
        copy = source.copy;
        unsigned long value = strtoul(copy, NULL, 10);

        hours = value/3600;
        minutes = (value - hours * 3600)/60;
        seconds = (value - hours*3600 - minutes*60);

        copy = hours + minutes + seconds;

        return *this;
    }

    getString(TimeLength copy){
        return copy;
    }

    static createZeroLength(TimeLength copy){
        copy = "0";
        return copy;
    }

private:
    char *copy;
    unsigned long hours;
    unsigned long minutes;
    unsigned long seconds;
};

int main(){

    TimeLength uptime("19592");
    std::cout << uptime << std::endl;

    TimeLength uptime2("20305");
    uptime = uptime2;

    std::cout << uptime.getString() << std::endl;

    std::cout << uptime.createZeroLength() << std::endl;

    return 0;
}