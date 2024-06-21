#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define MAX_ARG_LEN 8

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fifo> string \n", argv[0]);
        exit(1);
    }

    int pid = atoi(argv[1]);
    char buffer[MAX_ARG_LEN];

    strncpy(buffer, argv[2], MAX_ARG_LEN);

    union sigval value;

    value.sival_int = 42;
    value.sival_ptr = (void*) buffer;

   printf("Signal string: %s\n", value.sival_ptr);

    if (sigqueue(pid, SIGUSR1, value) == -1) {
        perror("kill");
        exit(1);
    }
}

