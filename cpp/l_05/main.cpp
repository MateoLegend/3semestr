#include <iostream>
#include <cstring>
#include <cstdlib>

class Item
{
public:
    const std::string& getName()    // do implementacji
    {
        return name;
    }
    unsigned int getID()            // do implementacji 
    {
        return id;
    }
    static unsigned int getCount()  // do implementacji 
    {
        return count;
    }


protected:
    Item(const std::string &name)   // do implementacji 
    : name(name), id(count++){}

private:
    /* Dodaj odpowiednie trzy zmienne,
       dwie dla danego obiektu i jedną dla całej klasy */
       std::string name;
       unsigned int id;
       static unsigned int count;       // dla całej klasy (static)


};

// inicjalizacja zmiennej statycznej
unsigned int Item::count = 0;


class Weapon : public Item
{
public:
    Weapon(const std::string &name) : Item(name) {};
    virtual float getDamage() = 0;
    virtual bool isBroken() = 0;
    virtual void use() = 0;
    virtual void repair() = 0;
    void print()    // do implementacji
    {
        if(!isBroken()){
            std::cout << "Weapon " << getName() << " " << getID() << " results in " << getDamage() << " of damage points." << std::endl;
        }
        else {
            std::cout << "Weapon " << getName() << " " << getID() << " cannot be used, as it is broken." << std::endl;
        }
    }
    virtual ~Weapon(){};
};

class Sword : public Weapon
{
public:
    Sword() : Weapon("Sword") {};
    ~Sword() { std::cout << "Sword object is being destroyed..." << std::endl; };
    virtual float getDamage() override // do implementacji 
    {
        return baseDamage * sharpness;
    }
    virtual bool isBroken() override   // do implementacji 
    {
        return sharpness<=0;
        /*
        if(sharpness==0){
            return 0;
        } else return 1;
        */
    }
    virtual void use() override        // do implementacji 
    {
        print();
        sharpness = sharpness - 0.1;
    }
    virtual void repair() override     // do implementacji 
    {
        sharpness = sharpness * 1.1;
        if(sharpness > 1){
            sharpness = 1;
        }
    }

private:
    const float baseDamage = 8.125;
    float sharpness = 0.5;
};

class Hammer : public Weapon
{
public:
    Hammer() : Weapon("Hammer") {};
    ~Hammer() { std::cout << "Hammer object is being destroyed..." << std::endl; };
    virtual float getDamage() override // do implementacji 
    {
        if(durability > 0){
            return damage;
        }
        return 0;
    }
    virtual bool isBroken() override   // do implementacji 
    {
        return durability == 0;
        // if(durability==0){
        //     return true;
        // } else return false;
    }
    virtual void use() override        // do implementacji
    {
        print();
        durability = durability - 1;
    }
    virtual void repair() override     // do implementacji
    {
        durability = defaultDurability;
    }

private:
    const unsigned int defaultDurability = 4;
    const float damage = 3.5;
    unsigned int durability = defaultDurability;
};



int main(){
    srand(time(NULL));

    Weapon *equipment[4] = {
        new Sword,
        new Hammer,
        new Sword,
        new Hammer
    };

    while(!equipment[0]->isBroken() || !equipment[1]->isBroken() || !equipment[2]->isBroken() || !equipment[3]->isBroken()){

        for(int i = 0; i<4; i++){
            if(!equipment[i]->isBroken()){
                equipment[i]->use();

                bool shouldRepair = (rand() % 10000) == 0; 
                if (shouldRepair)
                {
                    equipment[i]->repair();
                }
            }
        }
    }
    // destruktor ekwipunku, zwalniam pamięć
    for(int i = 0; i<4; i++){
        delete equipment[i];
    }

    return 0;
}