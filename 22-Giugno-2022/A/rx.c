#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>


#define MAX_ARG_LEN 8

int tx_pid;

void get_pid(int sig, siginfo_t *si, void *unused) {
    tx_pid = si->si_value.sival_int;
    printf("Pid received: %d\n", tx_pid);
}

void handler(int sig, siginfo_t *si, void *unused) {
    union sigval value = si->si_value;
    printf("Signal value: %c",(char) value.sival_int);
}

int main(int argc, char *argv[]) {
    
    struct sigaction sa;
    char buffer[MAX_ARG_LEN];

    sa.sa_sigaction = get_pid;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction1");
        return 1;
    }

    printf("Pid: %d\n", getpid());

    pause();
    sleep(3);

    sa.sa_sigaction = handler;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction2");
        return 1;
    }

    while(1) {
        kill(tx_pid, SIGUSR1);
        pause();
        sleep(3);
    }

    return 0;
}

