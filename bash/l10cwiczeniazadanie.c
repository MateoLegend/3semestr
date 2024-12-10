#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>



void usr1_handler(int signum){
    load_file(otwarty_plik);
}
void usr2_handler(int signum){
    clear buffer;
}



void handler(int signo)
{
	printf("Wystąpił sygnał %d (%s)\n", 
	       signo,
	       strsignal(signo));

	exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]){

    struct sigaction act = { 0 };

	act.sa_handler = &handler;

	if (sigaction(SIGUSR1, &act, NULL) == -1){
		exit(EXIT_FAILURE);
	}
    if (sigaction(SIGUSR2, &act, NULL) == -1){
		exit(EXIT_FAILURE);
	}
    if (sigaction(SIGINT, &act, NULL) == -1){
		exit(EXIT_FAILURE);
	}

    FILE *otwarty_plik = fopen( argv[1], "r" );
    if( otwarty_plik == false){
        printf( "Error! Nie udalo sie uzyskac dostepu do pliku.\n" );
        //return EXIT_FAILURE;
    }

    

    return 0;
}
