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

void handler(int sig, siginfo_t *si, void *unused) {
    printf("Signal received\n");
    printf("Signal value: %d\n", si->si_value.sival_int);
    printf("%s",(char*)si->si_value.sival_ptr);
}

int main(int argc, char *argv[]) {
    
    struct sigaction sa;
    char buffer[MAX_ARG_LEN];

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }


    printf("Pid: %d\n", getpid());

    pause();

    // Rest of your code

    return 0;
}

