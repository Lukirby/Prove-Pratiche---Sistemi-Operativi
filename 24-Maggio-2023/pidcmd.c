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
        printf("Usage: %s <cmd>\n", argv[0]);
        exit(1);
    }

    char C[MAX_PATH];

    for (int i=1; i<argc-1; i++) {
        strncpy(C, argv[i], MAX_PATH);
    }

    DIR *dir=opendir("/proc");
    
    for (struct dirent *d; (d=readdir(dir)) != NULL; ) {
        if (d->d_type == DT_DIR) {
            char path[MAX_PATH];
            snprintf(path, sizeof(path), "/proc/%s/cmdline", d->d_name);
            int fd=open(path, O_RDONLY);
            if (fd != -1) {
                char cmd[MAX_PATH];
                int n=read(fd, cmd, sizeof(cmd));
                cmd[n]='\0';
                if (strncmp(cmd, C, strlen(C)) == 0){
                    printf("%s\n", d->d_name);
                }
                close(fd);
            }
        }
    }

}