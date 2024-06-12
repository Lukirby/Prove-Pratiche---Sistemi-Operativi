#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {

    while(1){
        int fork_pid = fork();

        if(fork_pid == 0){
            if(execvp(argv[1], argv+1) == -1){
                perror("child error");
                exit(1);
            }
        } else
        if(fork_pid == -1){
            perror("fork error");
            exit(1);
        } else {
            printf("Child processing...\n");
            int status;
            int wait_pid = wait(&status);
            if(wait_pid == -1 || WIFEXITED(status) == 1){
                perror("command error");
                exit(1);
            };
        }
    }


}