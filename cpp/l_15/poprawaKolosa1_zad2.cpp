#include <iostream>
#include <cstring>

class CharacterModifier{
public:
    CharacterModifier(){
        std::cout << "Konstruktor oryginału" << std::endl;
    }

    virtual ~CharacterModifier(){
        std::cout << "Destruktor oryginału" << std::endl;
    }

    virtual std::string perform() const = 0;
};

class UpperCharacterModifier : public CharacterModifier{
public:
    UpperCharacterModifier(){
        std::cout << "Konstruktor klasy Upper" << std::endl;
    }

    ~UpperCharacterModifier(){
        std::cout << "Destruktor klasy Upper" << std::endl;
    }

    std::string perform() const override{
        return "upper";
    }
};

class LowerCharacterModifier : public CharacterModifier{
public:
    LowerCharacterModifier(){
        std::cout << "Konstruktor klasy Lower" << std::endl;
    }

    ~LowerCharacterModifier(){
        std::cout << "Destruktor klasy Lower" << std::endl;
    }

    std::string perform() const override{
        return "lower";
    }
};

void printCommand(CharacterModifier *cm){
    std::cout << cm->perform() << std::endl;
}


int main(){
    CharacterModifier *upperChar = new UpperCharacterModifier;
    CharacterModifier *lowerChar = new LowerCharacterModifier;

    printCommand(upperChar);
    printCommand(lowerChar);

    delete upperChar;
    delete lowerChar;

    return 0;
}