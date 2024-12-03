#include <iostream>
#include <cstring>
#include <cstdlib>

class TimeLength {
public:
    TimeLength(const char *_seconds) : copy(strdup(_seconds)){
        unsigned long value = strtoul(copy, NULL, 10);
        seconds = value % 60;
        minutes = (value / 60) % 60;
        hours = value / 3600;
    }
    ~TimeLength(){
        free(copy);
    }

    // konstruktor kopiujący
    TimeLength(const TimeLength &source){
        copy = strdup(source.copy);
        hours = source.hours;
        minutes = source.minutes;
        seconds = source.seconds;
    }

    friend std::ostream& operator<<(std::ostream &os, const TimeLength &t){
        std::cout << t.hours << "h " << t.minutes << "min " << t.seconds << "sec\n";
        return os;
    }

    char *getString() const {
        return copy;
    }

    static TimeLength& createZeroLength() {
        static TimeLength zero("0");
        return zero;
    }

private:
    char *copy;
    unsigned long hours;
    unsigned long minutes;
    unsigned long seconds;
};

int main(){
        /*Podpunkt b*/
    TimeLength uptime("19592");
    std::cout << "Podpunkt b:\n" << uptime << std::endl;

        /*Podpunkt c*/
    TimeLength newUptime(uptime);
    std::cout << "Podpunkt c:\n" << newUptime << std::endl;

        /*Podpunkt d*/
    std::cout << "Podpunkt d:\n" << uptime.getString() << std::endl;

        /*Podpunkt e*/
    std::cout << "Podpunkt e:\n" << uptime.createZeroLength() << std::endl;

    return EXIT_SUCCESS;
}