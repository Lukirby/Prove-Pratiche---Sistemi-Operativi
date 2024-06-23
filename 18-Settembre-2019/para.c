#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char ***prog = malloc(sizeof(char **)*argc);

    int j = 0;
    int k = 0;

    prog[j] = malloc(sizeof(char *));

    for (int i = 1; i < argc; i++) {
        if (argv[i] != NULL) {
            if (strcmp(argv[i], "//") == 0) {
                prog[j][k] = NULL;
                j++;
                k = 0;
                prog[j] = malloc(sizeof(char *));
            } else {
                prog[j] = realloc(prog[j], (k + 1) * sizeof(char *)); // Resize current "program"
                prog[j][k] = malloc(strlen(argv[i]) + 1);
                strcpy(prog[j][k],argv[i]);
                k++;
            }
        }
    }

    prog[j][k] = NULL;

    /* for (int i = 0; prog[i]!=NULL ; i++) {
        printf("Program %d: \n", i);
        for (int l = 0;prog[i][l]; l++) {
            printf("%s ", prog[i][l]);
        }
        printf("\n");
    } */

    for (int i = 0; prog[i] != NULL; i++) {
        if (fork() == 0) {
            execvp(prog[i][0], prog[i]);
            perror("execvp");
            return 1;
        }
    }

    for (int i = 0; prog[i] != NULL; i++) {
        wait(NULL);
    }

    return 0;
}