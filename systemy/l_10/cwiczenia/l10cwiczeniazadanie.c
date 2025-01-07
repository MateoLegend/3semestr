#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

/* Flagi */

volatile sig_atomic_t reload_flag = 0;  // Flaga sygnału dla SIGUSR1
volatile sig_atomic_t clear_flag = 0;   // Flaga sygnału dla SIGUSR2
volatile sig_atomic_t stop_flag = 0;    // Flaga sygnału dla SIGINT

/* Wskaźnik na dynamiczny bufor */
char *buffer = NULL;
size_t buffer_size = 0;

/* Ścieżka do pliku */
char *file_path = NULL;

/* Funkcja wczytująca zawartość pliku do bufora */
void load_file() {
    if (file_path == NULL) return;

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Nie można otworzyć pliku");
        return;
    }

    /* Kasowanie starego bufora */
    free(buffer);
    buffer = NULL;
    buffer_size = 0;

    /* Przechodzimy na koniec pliku, aby poznać jego rozmiar */
    fseek(file, 0, SEEK_END);
    buffer_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    /* Alokacja pamięci */
    buffer = (char *)malloc(buffer_size + 1);
    if (buffer == NULL) {
        perror("Błąd alokacji pamięci");
        fclose(file);
        return;
    }

    /* Wczytanie pliku do bufora */
    fread(buffer, 1, buffer_size, file);
    buffer[buffer_size] = '\0';  // Zakończenie bufora znakiem '\0'

    fclose(file);
    printf("\nPlik wczytano ponownie (%ld bajtów).\n", buffer_size);
}

/* Funkcja obsługi sygnału SIGUSR1 */
void handle_sigusr1(int sig) {
    reload_flag = 1;  // Ustawienie flagi do ponownego wczytania pliku
}

/* Funkcja obsługi sygnału SIGUSR2 */
void handle_sigusr2(int sig) {
    clear_flag = 1;  // Ustawienie flagi do wyczyszczenia bufora
}

/* Funkcja obsługi sygnału SIGINT */
void handle_sigint(int sig) {
    stop_flag = 1;  // Ustawienie flagi do zatrzymania programu
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Błąd: Nie podano ścieżki do pliku jako argument.\n");
        return -1;
    }

    file_path = argv[1];

    /* Przypisanie funkcji obsługi sygnałów */
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);
    signal(SIGINT, handle_sigint);

    /* Początkowe wczytanie pliku */
    load_file();

    while (1) {
        if (reload_flag) {
            reload_flag = 0;
            load_file();
        }

        if (clear_flag) {
            clear_flag = 0;
            free(buffer);
            buffer = NULL;
            buffer_size = 0;
            printf("\nZawartość bufora została wyczyszczona.\n");
        }

        if (stop_flag) {
            stop_flag = 0;
            printf("\nCzy na pewno chcesz zakończyć program? (y/n): ");
            char answer = getchar();
            if (answer == 'y' || answer == 'Y') {
                printf("Zamykanie programu...\n");
                free(buffer);
                return 0;
            } else {
                printf("Kontynuowanie działania programu...\n");
                // Opróżniamy bufor wejścia po getchar()
                while (getchar() != '\n');
            }
        }

        if (buffer != NULL) {
            printf("\nZawartość pliku:\n%s\n", buffer);
        } else {
            printf("\nBufor jest pusty.\n");
        }

        sleep(1);  // Czekamy 1 sekundę przed kolejnym wypisaniem
    }

    return 0;
}
