#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_ARGS 100
#define MAX_ARG_LEN 100

int main(int argc, char *argv[]){
    char *args[MAX_ARGS];
    char buffer[MAX_ARG_LEN];
    int arg_count = 0;
    int len;

    buffer[0] = '\0';
    
    mode_t mode = 0666;
    char *pipe = argv[1];
    mkfifo(pipe,mode);

    int fd = open(pipe,O_RDONLY);

    len = read(fd, buffer, MAX_ARG_LEN);

    for (int i = 0; i < len; i++) {
        if (buffer[i] == ' ') {
            arg_count++;
        }
    }

    printf("arg_count: %d\n", arg_count);
    int j = 0;
    int k = 0;
    for (int i = 0; i < arg_count; i++) {
        args[i] = (char *) malloc(MAX_ARG_LEN);
        while (buffer[j] != ' ') {
            args[i][k] = buffer[j];
            j++;
            k++;
        }
        args[i][k] = '\0';
        k = 0;
        j++;
        printf("args[%d]: %s\n", i, args[i]);
    }

    execvp(args[0], args);

    perror("execvp failed");
    return 1;

}