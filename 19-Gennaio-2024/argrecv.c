#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_ARGS 100
#define MAX_ARG_LEN 100

int main() {
    char *args[MAX_ARGS];
    char buffer[MAX_ARG_LEN];
    int arg_count = 0;
    int len;

    len = read(STDIN_FILENO, buffer, MAX_ARG_LEN);

    // Parse the string and fill the args array
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