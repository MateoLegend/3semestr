#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    const char pathname[] = "/tmp/fifo";
    if (mkfifo(pathname, 0666) != 0){
        exit(EXIT_FAILURE);
    }

    int fd = open(pathname, O_RDONLY);
    if (fd < 0){
        exit(EXIT_FAILURE);
    }

    ssize_t length = 0;
    while(length != -1){
        char buffer[1024];
        length = read(fd, buffer, sizeof(buffer));
        if (length > 0)
            write(STDOUT_FILENO, buffer, length);
    }

    close(fd);
    return 0;
}