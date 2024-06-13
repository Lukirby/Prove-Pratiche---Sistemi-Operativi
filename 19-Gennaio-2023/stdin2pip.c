#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 1024

function int arg_count(char *buffer) {
    int arg_count = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
            arg_count++;
        }
    }
    return arg_count;
}

function void fill_arg(char *buffer, char *args) {
    char *token = strtok(buffer, " ");
    int j = 0;
    while (token != NULL) {
        args[j] = token;
        token = strtok(NULL, " ");
        j++;
    }
}

int main (int argc, char *argv[]) {
    char buffer[MAX];
    char buffer2[MAX] = "";  // Initialize buffer2 to an empty string
    ssize_t bytesRead;

    while (read(STDIN_FILENO, buffer, MAX - 1) > 0) {
        //buffer[bytesRead] = '\0';  // Null-terminate the string
        strcat(buffer2, buffer);
    }

    if (bytesRead == -1) {
        perror("Error reading from stdin");
        exit(EXIT_FAILURE);
    }

    printf("Read %s", buffer2);

    char* cmd1 = malloc(MAX);    
    char* cmd2 = malloc(MAX);
    char* token = strtok(buffer2, "\n");
    cmd1 = token;
    token = strtok(NULL, "\n");
    cmd2 = token;

    if(fork()){
        wait(NULL);
    } else {
        int arg_count = arg_count(cmd1);

        char *args[arg_count];

        fill_arg(cmd1, args);

        execvp(args[0], args);
    }


    int arg_count = arg_count(buffer2);

    char *args[arg_count];

    fill_arg(buffer2, args);
    

    return 0;
}

/* #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 1024

int main (int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid;
    char buffer[MAX];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        close(pipefd[0]);  // Close unused read end

        // Redirect stdout to the write end of the pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        execvp(args[0], args);
        perror("execvp");  // execvp only returns on error
        exit(EXIT_FAILURE);
    } else {  // Parent process
        close(pipefd[1]);  // Close unused write end

        // Read from the pipe
        ssize_t bytesRead;
        while ((bytesRead = read(pipefd[0], buffer, MAX - 1)) > 0) {
            buffer[bytesRead] = '\0';  // Null-terminate the string
            printf("Read: %s", buffer);
        }

        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        close(pipefd[0]);  // Close the read end of the pipe
    }

    return 0;
} */