#include <sys/timerfd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main (int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <n-times>,<interval>,<string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Assuming argv[1] contains the input string "<n-times>,<interval>,<string>"
        char *token;
        int n_times;
        char *interval = malloc(100*sizeof(char));
        int interval_sec;
        int interval_nsec;
        char *string;
        
        // Extract n-times as integer
        token = strtok(argv[1], ",");
        n_times = atoi(token);
        
        // Extract interval as double
        token = strtok(NULL, ",");
        strcpy(interval, token);

        // Extract the remaining string
        string = strtok(NULL, ",");

        char* token2 = strtok(interval, ".");
        interval_sec = atoi(token2);
        token2 = strtok(NULL, ".");
        interval_nsec = atoi(token2)*1000000;   
        
        printf("n_times: %d, interval: %d.%d, string: %s\n", n_times, interval_sec,interval_nsec, string);

    struct timespec now;

    clock_gettime(CLOCK_REALTIME, &now);

    int fd;

    fd = timerfd_create(CLOCK_REALTIME, 0);

    struct itimerspec new_value;

    new_value.it_value.tv_sec = now.tv_sec + interval_sec;
    new_value.it_value.tv_nsec = now.tv_nsec+ interval_nsec;
    new_value.it_interval.tv_sec = interval_sec;
    new_value.it_interval.tv_nsec = interval_nsec;

    struct timespec start_value;
    struct timespec current_value;
    timerfd_settime(fd, TFD_TIMER_ABSTIME, &new_value, NULL);
    clock_gettime(CLOCK_REALTIME,&start_value);
    int sec;
    int nsec;

    for (int i = 0; i < n_times; i++) {
        u_int64_t expirations;
        read(fd, &expirations, sizeof(expirations));
        clock_gettime(CLOCK_REALTIME,&current_value);
        sec = current_value.tv_sec - start_value.tv_sec;
        nsec = current_value.tv_nsec - start_value.tv_nsec;
        printf("%d.%d %s\n", sec,nsec, string);

    }

}