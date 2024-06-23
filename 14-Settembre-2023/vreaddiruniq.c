#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

char** vreaddir(const char *path) {
    DIR* dir = opendir(path);
    if (dir == NULL) {
        return NULL;
    }
    size_t size = 0;
    int count = 0;
    for(struct dirent *entry = readdir(dir); entry != NULL; entry = readdir(dir)) {
        if (entry->d_type == DT_REG) {
            count++;
            size+=strlen(entry->d_name) + 1;
        }
    }
    char **files = malloc((count + 1) * sizeof(char*) + size);
    char* name_block = (char *)(files + count + 1);
    int i = 0;
    rewinddir(dir);
    for(struct dirent *entry = readdir(dir); entry != NULL; entry = readdir(dir)) {
        if (entry->d_type == DT_REG) {
            files[i] = name_block;
            strcpy(files[i], entry->d_name);
            name_block += strlen(entry->d_name) + 1;
            i++;
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