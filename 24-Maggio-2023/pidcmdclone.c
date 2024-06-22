#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_PATH 512



int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <pid>\n", argv[0]);
        exit(1);
    }

    char cmd[MAX_PATH];
    char environ[MAX_PATH*100];

    DIR* dirname = opendir("/proc");

    for(struct dirent *d; (d=readdir(dirname)) != NULL; ) {
        if (d->d_type == DT_DIR && atoi(d->d_name) == atoi(argv[1])){
            char path[MAX_PATH];
            snprintf(path, sizeof(path), "/proc/%s/cmdline", d->d_name);
            int fd=open(path, O_RDONLY);
            if (fd != -1) {
                int n=read(fd, cmd, sizeof(cmd));
                cmd[n]='\0';
                close(fd);
            } else {
                perror("not able to cmd file");
            }
            snprintf(path, sizeof(path), "/proc/%s/environ", d->d_name);
            fd=open(path, O_RDONLY);
            if (fd != -1) {
                int n=read(fd, environ, sizeof(environ));
                environ[n]='\0';
                
                close(fd);
            } else {
                perror("not able to environ file");
            }
            char *args[100];
            int i = 0;
            args[i] = strtok(cmd, "\00");
            while (args[i] != NULL && i < 99) {
                i++;
                args[i] = strtok(NULL, "\00");
            }
            for (int j=0; j<i; j++) {
                printf("%s\n", args[j]);
            }

            // Create a null-terminated array of environment variables
            char *env_vars[100];
            i = 0;
            env_vars[i] = strtok(environ, "\0");
            while (env_vars[i] != NULL && i < 99) {
                i++;
                env_vars[i] = strtok(NULL, "\0");
            }
            for (int j=0; j<i; j++) {
                printf("%s\n", env_vars[j]);
            }
            execve(args[0], args, env_vars);
        }
    }

}