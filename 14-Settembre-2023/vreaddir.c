#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

char** vreaddir(const char *path) {
    DIR* dir = opendir(path);
    if (dir == NULL) {
        return NULL;
    }
    char **files = malloc(sizeof(char*));
    int i = 0;
    for(struct dirent *entry = readdir(dir); entry != NULL; entry = readdir(dir)) {
        if (entry->d_type == DT_REG) {
            files[i] = malloc(strlen(entry->d_name) + 1);
            strcpy(files[i], entry->d_name);
            i++;
            files = realloc(files, (i + 1) * sizeof(char*));
        }
    }
    files[i] = NULL;
    return files;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return 1;
    }
    char **files = vreaddir(argv[1]);
    if (files == NULL) {
        fprintf(stderr, "Error reading directory\n");
        return 1;
    }
    for (int i = 0; files[i] != NULL; i++) {
        printf("%s\n", files[i]);
    }
    return 0;
}