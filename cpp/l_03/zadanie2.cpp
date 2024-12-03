#include <iostream>
#include <cstring>

class Person {
public:
    Person(unsigned int _pesel, const char* _name, const char* _surname)
    : pesel(_pesel), name(strdup(_name)), surname(strdup(_surname)) {}

/*Konstruktor kopiujący*/
    Person(const Person &source){
        pesel = source.pesel;
        name = source.name;
        surname = source.surname;
    }

/*Destruktor*/
    ~Person(){
        // free(name);
        // free(surname);
        delete [] name;
        delete [] surname;
    }

/*Operator przypisania*/
    Person& operator=(const Person &source) {
        free(name);
        free(surname);

        pesel = source.pesel;
        name = strdup(source.name);
        surname = strdup(source.surname);
        
        return *this;
    }

private:
    unsigned int pesel;
    char *name;
    char *surname;
};

int main() {
    Person p(1234567890, "Robert", "Kowalski");
    Person p2(p); /* Konstruktor kopiujący */
    Person p3(1234567890, "Adam", "Lewandowski");
    p = p3; /* Operator przypisania */
    return 0;
}