#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    char *dir = getcwd(NULL, 0);
    printf("Dir: %s\n", dir);
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
}