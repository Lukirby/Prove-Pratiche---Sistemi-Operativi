#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#define MAX_LEN 100

int main(int argc, char *argv[]) {
    int opt;
    int n_processes;
    char* file_source=malloc(MAX_LEN*sizeof(char));
    char* file_dest=malloc(MAX_LEN*sizeof(char));

    // Define accepted options. The colon after 'f' indicates it expects an argument.
    opt = getopt(argc, argv, "j:");
    if (opt == -1) {
        n_processes = 2;
        file_source=argv[optind];
        file_dest=argv[optind+1];
    } else {
        n_processes = atoi(optarg);
        file_source=argv[optind];               
        file_dest=argv[optind+1];
    }

    printf("Processes: %d\n", n_processes);
    printf("Source: %s\n", file_source);
    printf("Destination: %s\n", file_dest);

    int fd = open(file_source, O_RDONLY);
    int fd_dest = open(file_dest, O_WRONLY);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    __off_t file_size = lseek(fd, 0, SEEK_END);
    printf("File size: %zu\n", file_size);
    size_t chunk_size = (size_t) (file_size / n_processes);
    printf("Chunk size: %zu\n", chunk_size);

    for (int i = 0; i < n_processes; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Error forking");
            return 1;
        }

        if (pid == 0) {
            printf("Child process %d\n", i);
            __off_t offset = i * chunk_size;
            if (i == n_processes - 1) {
                chunk_size += file_size - (chunk_size * n_processes);
            }
            char* buffer = malloc(chunk_size);
            pread(fd, buffer, chunk_size, offset);
            pwrite(fd_dest, buffer, chunk_size, offset);
            exit(0);
        }
    }    

    return 0;
}