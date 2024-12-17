#include <sys/mman.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TAB_LENGTH 1
typedef struct shared {
    int tab[TAB_LENGTH];
    pthread_mutex_t mutex;
} shared_t;

#define DIGIT_COUNT 5
struct context {
    unsigned long count[DIGIT_COUNT];
    pthread_mutex_t mutex;
};


int main (int argc, char* argv[]) {
    struct stat statbuf;

    /* TODO: sprawdzic ile jest argumentow argc*/
    if (argc != 3){
        printf("Podaj poprawną liczbę argumentów. Podano ich %d.", argc);
        return -1;
    }
    printf("argc=%d\n", argc);
    int fd = open(argv[1], O_RDONLY);
    printf("fd=%d", fd);
    fstat(fd, &statbuf);
    printf("len=%d\n", statbuf.st_size);
    char *content = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    /* TODO: sprawdzic ret value z mmap*/
    printf("content ptr=%p\n", content);
    /* alokacja pamieci wspoldzielonej */

    int prot = PROT_READ | PROT_WRITE; // odczyt i zapis
    int vis = MAP_SHARED | MAP_ANONYMOUS;
    shared_t *shr = (shared_t*)mmap(NULL, sizeof(shared_t), prot, vis, -1, 0);
    if (shr == NULL)
        return -1;

    for (int i = 0; i < TAB_LENGTH; i++){
        shr->tab[i] = 0;
    }

    pthread_mutexattr_t mutexattr;
    if (pthread_mutexattr_init(&mutexattr) != 0)
        return -2;
    if (pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED) != 0)
        return -3;
    if (pthread_mutex_init(&shr->mutex, &mutexattr) != 0)
        return -4;

    for(int i = 0; i < statbuf.st_size; i++){
        /* [48, 57]*/
        if (content[i] >= '0' && content[i] <= '9'){
            int val = content[i] - '0'; // content[i] - 48
            // zwiekszyc odpowiednia wartosc w tablicy, ktora zlicza ilosc wystapien
            shr->tab[val]++;
        }
    }

    /* TODO: FORK w pętli i podział zakresów, następnie waitpid dla każdego procesu */
    
    for (int i = 0; i < TAB_LENGTH; i++){
        printf("%d = %d\n", i, shr->tab[i]);
    }
    
    munmap(content, sizeof(shared_t));
    close(fd);
    return 0;
}