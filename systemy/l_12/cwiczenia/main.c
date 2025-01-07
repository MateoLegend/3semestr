#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define TAB_LENGTH 10

typedef struct {
    int tab[TAB_LENGTH];
    pthread_mutex_t mutex;
} shared_t;

typedef struct {
    const char* content;
    size_t start;
    size_t end;
    shared_t* shared;
} thread_args_t;

void* count_digits(void* args) {
    thread_args_t* targs = (thread_args_t*)args;
    const char* content = targs->content;
    size_t start = targs->start;
    size_t end = targs->end;
    shared_t* shared = targs->shared;

    for (size_t i = start; i < end; ++i) {
        if (content[i] >= '0' && content[i] <= '9') {
            int val = content[i] - '0';
            pthread_mutex_lock(&shared->mutex);
            shared->tab[val]++;
            pthread_mutex_unlock(&shared->mutex);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Poprawne wypisanie: %s <filename> <num_threads>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    int num_threads = atoi(argv[2]);
    if (num_threads <= 0) {
        fprintf(stderr, "Liczba threads musi byc wieksza niz 0.\n");
        return EXIT_FAILURE;
    }

    // Open the file
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Błąd w otwieraniu pliku\n");
        return EXIT_FAILURE;
    }

    struct stat statbuf;
    if (fstat(fd, &statbuf) != 0) {
        perror("Błąd w pobraniu danych pliku\n");
        close(fd);
        return EXIT_FAILURE;
    }

    size_t file_size = statbuf.st_size;
    char* content = malloc(file_size);
    if (!content) {
        perror("Błąd w alokacji pamięci\n");
        close(fd);
        return EXIT_FAILURE;
    }

    if (read(fd, content, file_size) != file_size) {
        perror("Błąd odczytu pliku\n");
        free(content);
        close(fd);
        return EXIT_FAILURE;
    }
    close(fd);

    // inicjacja struktury shared_t
    shared_t shared = { .tab = {0} };
    pthread_mutex_init(&shared.mutex, NULL);

    // tworzenie threads
    pthread_t threads[num_threads];
    thread_args_t thread_args[num_threads];
    size_t chunk_size = file_size / num_threads;
    size_t remainder = file_size % num_threads;

    size_t start = 0;
    for (int i = 0; i < num_threads; ++i) {
        size_t end = start + chunk_size + (i < remainder ? 1 : 0);
        thread_args[i] = (thread_args_t){ .content = content, .start = start, .end = end, .shared = &shared };
        pthread_create(&threads[i], NULL, count_digits, &thread_args[i]);
        start = end;
    }

    // Czekajka na zakonczenie wątków
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Print
    for (int i = 0; i < TAB_LENGTH; ++i) {
        printf("%d = %d\n", i, shared.tab[i]);
    }

    // Czyszczenie
    pthread_mutex_destroy(&shared.mutex);
    free(content);

    return EXIT_SUCCESS;
}