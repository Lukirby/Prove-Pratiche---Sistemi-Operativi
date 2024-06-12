#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define MAX_ARG_LEN 100

void retrive_data(char* buffer, pid_t* pid, int *sig){
    int arg_count=0;
    
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == ' ') {
            arg_count++;
        }
    }
    
    if(arg_count!=1){
	*pid = -1;
	*sig = -1;
        return;
    }
    
    char *first_part;
    char *second_part;

    // Usa strtok per ottenere la prima parte della stringa
    first_part = strtok(buffer, " ");
    
    // Usa strtok per ottenere la seconda parte della stringa
    second_part = strtok(NULL, " ");
    
    *pid = atoi(first_part);
    *sig = atoi(second_part);
    
    return;
}


int main(int argc, char *argv[]) {
    

    int sig = -1;
    pid_t pid = -1;

    int fd;
    char buffer[MAX_ARG_LEN];
    

    while (1){
        mkfifo(argv[1], 0666);
        memset(buffer, 0, MAX_ARG_LEN);
        fd = open(argv[1], O_RDONLY);

        read(fd, buffer, MAX_ARG_LEN);
        if (strcmp(buffer,"FINE\n")==0) {
           printf("%s",buffer);
            break;
        } else {
            retrive_data(buffer,&pid,&sig);
            if(pid == -1 || sig == -1){
                printf("Bad Formatting\n");
            } else {
                printf("Pid: %d , Sig: %d\n",pid,sig);
                kill(pid, sig);
                pid = -1;
                sig = -1;
            }
        }
        close(fd);
        // delete the FIFO
        unlink(argv[1]);
    }
    close(fd);
    // delete the FIFO
    unlink(argv[1]);

    
}
