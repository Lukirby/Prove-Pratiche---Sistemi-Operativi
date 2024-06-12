#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define MAX_ARG_LEN 100

int main(int argc, char *argv[]){
    char pid_sig[MAX_ARG_LEN]; 
    sprintf(pid_sig,"%d %d",getpid(),SIGUSR1);
    printf("%s\n",pid_sig);
    int fd;
    fd = open("pipe", O_WRONLY);
    printf("%d\n",fd);
    write(fd, pid_sig, strlen(pid_sig));
    int sig=0;
    while(sig!=SIGUSR1){
        sig = pause();
        printf("Received %d\n",sig);
    }
    return 0;
}