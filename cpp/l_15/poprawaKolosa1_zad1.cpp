#include <iostream>
#include <cstdlib>
#include <cstring>

class MyString{
private:
    char *content;
    size_t memorySize;
    static int stringCount; // do e)
public:
    /* Konstruktor */
    MyString(const char *value): content(strdup(value)), memorySize(strlen(value)){
        stringCount++;
    }

    /* Destruktor */
    ~MyString(){
        free(content);
        stringCount--;
    }

    /* Przeciążenie operatora << */
    friend std::ostream& operator<<(std::ostream &os, const MyString &t){
        std::cout << t.content << std::endl;
        return os;
    }

    /* Konstruktor kopiujący */
    MyString(const MyString &source){
        content = strdup(source.content);
        memorySize = source.memorySize;
        stringCount++;
    }

    /* d) */
    size_t size() const{
        return memorySize;
    }

    /* e) */
    static int getStringCount(){
        return stringCount;
    }
};

int MyString::stringCount = 0;

int main(){
    /* Testowanie przeciążenia operatora << */
    MyString alaMaKota("Ala ma kota");
    std::cout << alaMaKota << std::endl;

    /* Testowanie konstruktora kopiującego */
    MyString kolejnaAla(alaMaKota);
    std::cout << kolejnaAla << std::endl;

    /* Testowanie metody size() */
    std::cout << kolejnaAla.size() << std::endl;

    /* Testowanie e) */
    std::cout << "Ilość utworzonych MyString: " << MyString::getStringCount() << std::endl;
    return 0;
}