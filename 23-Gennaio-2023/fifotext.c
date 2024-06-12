#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_ARG_LEN 100

int areEqual(char str1[], char str2[]) {
    int i = 0;

    // Continue while neither string has reached the end
    while (str1[i] != '\0' && str2[i] != '\0') {
        // If characters are not equal, return 0 (false)
        if (str1[i] != str2[i]) {
            return 0;
        }
        i++;
    }

    // If both strings have reached the end, they are equal
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 1;
    }

    // If only one has reached the end, they are not equal
    return 0;
}


int main(int argc, char *argv[]) {

    int fd;
    char buffer[MAX_ARG_LEN];
    mkfifo(argv[1], 0666);

    while (1){
        memset(buffer, 0, MAX_ARG_LEN);
        fd = open(argv[1], O_RDONLY);

        read(fd, buffer, MAX_ARG_LEN);
        
        if (strcmp(buffer,"FINE\n")==0) {
            break;
        } else {
            printf("%s\n", buffer);
        }

        close(fd);
    }

    
    // delete the FIFO
    unlink(argv[1]);

}