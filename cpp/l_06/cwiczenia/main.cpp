#include <iostream>

class Spell{
private:
    std::string destruction;
    std::string restoration;
    std::string illusion;
    std::string alteration;
    std::string conjuration;
    virtual std::string masterLevel() = 0; // novice, appretnice, adept, expert, master
public:
    Spell(const std::string &_destruction, const std::string &_restoration, const std::string &_illusion, const std::string &_alteration, const std::string &_conjuration)
        : destruction(_destruction), restoration(_restoration), illusion(_illusion), alteration(_alteration), conjuration(_conjuration) {}


    Spell(const std::string &_destruction, const std::string &_restoration, const std::string &_illusion, const std::string &_alteration)
        : destruction(_destruction), restoration(_restoration), illusion(_illusion), alteration(_alteration) {}

    Spell(const std::string &_destruction, const std::string &_restoration, const std::string &_illusion)
        : destruction(_destruction), restoration(_restoration), illusion(_illusion) {}

    Spell(const std::string &_destruction, const std::string &_restoration)
        : destruction(_destruction), restoration(_restoration) {}    

    Spell(const std::string &_destruction)
        : destruction(_destruction) {}


    ~Spell();
};

class Student : Spell{
private:
    std::string name;
    int *bellyVolume;  // objetosc brzucha, na podstawie umiejetnosci?

public:
    Student(const std::string &_destruction, const std::string &_restoration, const std::string &_illusion, const std::string &_alteration, const std::string &_conjuration, const std::string &_name, int *_bellyVolume)
        : Spell(_destruction, _restoration, _illusion, _alteration, _conjuration), name(_name), bellyVolume(_bellyVolume) {}
    
    ~Student();

};


int main(){





    return 0;
}