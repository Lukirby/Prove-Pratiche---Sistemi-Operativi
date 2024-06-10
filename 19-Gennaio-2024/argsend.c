#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buffer[100];
    buffer[0] = '\0';
    for (int i = 1; i < argc; i++) {
        strcat(buffer, argv[i]);
        strcat(buffer, " ");
    }
    write(STDOUT_FILENO, buffer, 100);
    return 0;
}