#include <sys/timerfd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main (int argc, char *argv[]) {


    for (int i = 1; i < argc; i++) {
        printf("Creating child process for %s\n", argv[i]);
        if(fork()==0){
            execlp("./tfdtest","tfdtest", argv[i]);
        }
    }

    for (int i = 1; i < argc; i++) {
        wait(NULL);
    }

}