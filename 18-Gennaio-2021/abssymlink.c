#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>


#define MAX_PATH 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    DIR *dir = opendir(argv[1]);

    char * buffer = malloc(MAX_PATH);

    char path[MAX_PATH];
    char resolved_path[MAX_PATH];
    char new_path[MAX_PATH];

    for(struct dirent *d; (d=readdir(dir)) != NULL; ) {
        if (d->d_type == DT_LNK) {
            snprintf(path, sizeof(path), "%s/%s", argv[1], d->d_name);
            readlink(path, buffer, MAX_PATH);
            printf("%s -> %s\n", d->d_name, buffer);
            realpath(path, resolved_path);
            printf("Real path: %s\n", resolved_path);
            snprintf(new_path, sizeof(new_path), "%s/%s_abs", argv[1], d->d_name);
            symlink(resolved_path,new_path);
        }
    }

    
}