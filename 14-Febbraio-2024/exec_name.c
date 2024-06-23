#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_PATH 1020

int search_name(char* dir_name,char *name, char *args[]) {
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    for (struct dirent *d; (d = readdir(dir)) != NULL; ) {
        if (d->d_type == DT_REG) {
            char path[MAX_PATH];
            snprintf(path, MAX_PATH, "%s/%s", dir_name, d->d_name);
            int fd = open(path, O_RDONLY);
            if (fd == -1) {
                perror("open");
                continue;
            }
            if(strstr(d->d_name, name) == NULL) {
                close(fd);
                continue;
            }
            char header[4];
            if (read(fd, header, 4) == -1) {
                perror("read");
                close(fd);
                continue;
            }
            close(fd);
            if (header[0] == '#' && header[1] == '!' && (header[2] == '/' || header[2] == 'u' || header[2] == 'b')) {
                printf("%s: script\n", path);
                if(fork() == 0) {
                    execvp(path, args);
                } else {
                    wait(NULL);
                }
            } else if (header[0] == 0x7f && header[1] == 'E' && header[2] == 'L' && header[3] == 'F') {
                printf("%s: ELF executable\n", path);
                if(fork() == 0) {
                    execvp(path, args);
                } else {
                    wait(NULL);
                }
            }
        } else if (d->d_type == DT_DIR) {
            if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) {
                continue;
            } else {
                char path[MAX_PATH];
                snprintf(path, MAX_PATH, "%s/%s", dir_name, d->d_name);
                search_name(path, name, args);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <name> <args>\n", argv[0]);
        return 1;
    }

    char *name = argv[1];

    char **args = argv+2;

    char C[MAX_PATH] = ".";

    //getcwd(C, MAX_PATH);


    search_name(C, name, args);

}