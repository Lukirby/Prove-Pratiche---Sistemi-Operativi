#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX 1024

int arg_count(char *buffer) {
    int arg_count = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
            arg_count++;
        }
    }
    return arg_count;
}

void fill_arg(char *buffer, char *args) {
    char *token = strtok(buffer, " ");
    int j = 0;
    while (token != NULL) {
        args[j] = *token;
        token = strtok(NULL, " ");
        j++;
    }
}

int main (int argc, char *argv[]) {
    char buffer[MAX];
    char buffer2[MAX] = "";  // Initialize buffer2 to an empty string
    ssize_t bytesRead;

    while (read(STDIN_FILENO, buffer, MAX - 1) > 0) {
        strcat(buffer2, buffer);
    }

    buffer2[strlen(buffer2)] = '\0';  // Null-terminate the string

    char* token = strtok(buffer2, "\n");
        char *cmd= malloc((strlen(token) + 1) * sizeof(char));
        strcpy(cmd, token);
        token = strtok(NULL, "\n");
        char *cmd2= malloc((strlen(token) + 1) * sizeof(char));
        strcpy(cmd2, token);
    
        strcat(cmd, " | ");
        strcat(cmd, cmd2);



    int fd = open("file.bash", O_CREAT | O_RDWR , S_IRWXU|S_IRWXG|S_IRWXO);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    write(fd, cmd, strlen(cmd));

    if(fork()){
        execlp("bash", "bash", "file.bash", NULL);
    } else {
        wait(NULL);
        close(fd);
        unlink("file.bash");
    }

    return 0;
}
