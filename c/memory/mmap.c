#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>
#include <getopt.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/mman.h>


int main()
{
    void *addr = NULL;
    pid_t pid = 0;
    
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;
    if (0 != pthread_mutexattr_init(&attr)) {
        perror("pthread_mutexattr_init");
        return -1;
    }
    if (0 != pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)) {
        perror("pthread_mutexattr_setpshared");
        return -1;
    }

    if (0 != pthread_mutex_init(&mutex, &attr)) {
        perror("pthread_mutex_init");
        return -1;
    }
    if (MAP_FAILED == (addr = mmap(NULL, 10000, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0))) {
        perror("mmap");
        return -1;
    }
    *(int *)addr = 111;

    if (0 == (pid = fork())) {
        if (0 != pthread_mutex_lock(&mutex)) {
            perror("pthread_mutex_lock");
        }
        if (0 != pthread_mutex_unlock(&mutex)) {
            perror("pthread_mutex_unlock");
        }
        printf("son: %d\n", *(int *)addr);
        sleep(1);
        *(int *)addr = 112;
        sleep(2);
        printf("son: %d\n", *(int *)addr);
    } else if (pid > 0) {
        if (0 != pthread_mutex_lock(&mutex)) {
            perror("pthread_mutex_lock");
        }
        if (0 != pthread_mutex_unlock(&mutex)) {
            perror("pthread_mutex_unlock");
        }
        printf("father: %d\n", *(int *)addr);
        sleep(2);
        printf("father: %d\n", *(int *)addr);
        *(int *)addr = 113;
        wait(pid);
    } else {
        return -1;
    }

    return 0;
}
