#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int depth = 0;

    char *path = argv[1];

    char *dir = malloc(100*sizeof(char));

    if(argc > 2){
        depth = atoi(argv[2]);
        strcpy(dir, argv[3]);
    } else {
        strcpy(dir, argv[1]);
    }

    for (int i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("%s\n", dir);

    struct dirent *dp;
    DIR *fd = opendir(path);
    dp = readdir(fd);

    while (dp != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            if(fork()){
                wait(NULL);
            } else {
                char depth_str[10];
                sprintf(depth_str, "%d", depth + 1);
                path = strcat(path, "/");
                path = strcat(path, dp->d_name);
                execlp("./tree", "./tree",path,depth_str,dp->d_name,NULL);            
            }
            
        }
        dp = readdir(fd);
    }
    return 0;
}

