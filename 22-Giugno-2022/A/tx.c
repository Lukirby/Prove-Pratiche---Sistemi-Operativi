#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define MAX_ARG_LEN 8

void handler(int sig, siginfo_t *si, void *unused) {
    
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fifo> string \n", argv[0]);
        exit(1);
    }

    int pid = atoi(argv[1]);
    char buffer[MAX_ARG_LEN];

    struct sigaction sa;
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction2");
        return 1;
    }

    strncpy(buffer, argv[2], MAX_ARG_LEN);
    union sigval value;

    for (int i = -1; i < MAX_ARG_LEN; i++) {
        if (i == -1) {
            value.sival_int = getpid();
        } else {
            if(buffer[i] == '\0') {
                break;
            }
            value.sival_int = (int) buffer[i];
            if (sigqueue(pid, SIGUSR1, value) == -1) {
                perror("kill");
                exit(1);
            }
        }
        if (sigqueue(pid, SIGUSR1, value) == -1) {
            perror("kill");
            exit(1);
        }
        pause();
        sleep(3);
    }

}

