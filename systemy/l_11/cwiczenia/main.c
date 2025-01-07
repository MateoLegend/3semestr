#include <sys/mman.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define TAB_LENGTH 6
typedef struct shared {
    int tab[TAB_LENGTH];
    pthread_mutex_t mutex;
} shared_t;

// #define DIGIT_COUNT 5
// struct context {
//     unsigned long count[DIGIT_COUNT];
//     pthread_mutex_t mutex;
// };


int main (int argc, char* argv[]) {
    struct stat statbuf;
    printf("argc=%d\n", argc);

    /* TODO: sprawdzic ile jest argumentow argc*/
    if (argc != 3){
        printf("Podaj poprawną liczbę argumentów. Podano ich %d.\n", argc-1);
        return -1;
    }
    int fd = open(argv[1], O_RDONLY);
    printf("fd=%d\n", fd);
    fstat(fd, &statbuf);
    printf("len=%ld\n", statbuf.st_size);
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
    int num_processes = atoi(argv[2]);
    
    // for(int i = 0; i < num_processes; i++){
    //     pthread_mutex_lock(&shr->mutex);
    //     pid_t pid = fork();
    //     if (pid == -1){
    //         printf("Klopoty");
    //         return -5;
    //     }
    //     else if (pid == 0){
    //         printf("Dzieciak");
    //         return 0;
    //     }
    //     pthread_mutex_unlock(&shr->mutex);
    //     waitpid(pid, NULL, 0);
    // }

    char *endptr;

    int buff_size = 0;
    int num_args = strtol(argv[2], &endptr, 10);
    int *tab = (int*)(malloc(sizeof(int)*num_args));
    if (*endptr != '\0'){
        printf("Drugi argument nie jest liczbą");
        return -5;
    }

    pid_t pid;
    int rest = statbuf.st_size % num_args;
    int file_pieces = statbuf.st_size / num_args;

    for(int i = 0; i < num_args; i++){
        if(i+1 == num_args)
            buff_size += (statbuf.st_size + rest);
        else
            buff_size += statbuf.st_size;

        tab[i] = getpid();
        pid = fork();
        if (pid == -1){
            perror("Błąd przy tworzeniu nowego procesu");
            return -6;
        }
        if(pid == 0){
            for(int j = 0; j < buff_size; j + buff_size){
                if (content[j] >= '0' && content[j] <= '9'){
                int val = content[j] - '0'; // content[j] - 48
                // zwiekszyc odpowiednia wartosc w tablicy, ktora zlicza ilosc wystapien
                pthread_mutex_lock(&shr->mutex);
                shr->tab[val]++;
                pthread_mutex_unlock(&shr->mutex);
                }
            }
            exit(0);
        }

    }
    
    if (pid > 0){
        for(int i = 0; i < TAB_LENGTH; i++){
            printf("%d = %d\n", i, shr->tab[i]);
        }

        for(int i = 0; i < num_args; i++){
            waitpid(tab[i], NULL, 0);
        }

        pthread_mutex_destroy(&shr->mutex);
        munmap(shr, sizeof(shared_t));
        munmap(content, statbuf.st_size);
        close(fd);
        pthread_mutexattr_destroy(&mutexattr);
    }

    return 0;
}