#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/mman.h>

void *thread_proc(void *arg)
{
    while (1) {
        sleep(1);
    }
}

void process_proc()
{

}

int main()
{
    pid_t pid;
    pthread_t tid;
    pthread_mutex_t *mutex;
    pthread_mutexattr_t attr;
    if (MAP_FAILED == (mutex = mmap(NULL, sizeof(pthread_mutex_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0))) {
        perror("mmap");
        return -1;
    }
    
    if (0 != pthread_mutexattr_init(&attr)) {
        return -1;
    }

    if (0 != pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)) {
        return -1;
    }

    if (0 != pthread_mutex_init(mutex, &attr)) {
        return -1;
    }
    
    if (0 != pthread_create(&tid, NULL, thread_proc, NULL)) {
        return -1;
    }

    if (0 == (pid = fork())) {
        if (0 != pthread_mutex_lock(mutex)) {
            printf("error1\n");
        }
        sleep(2);
        printf("child do first.\n");
        if (0 != pthread_mutex_unlock(mutex)) {
            printf("error2\n");
        }
    } else if (pid > 0) {
        sleep(1);
        if (0 != pthread_mutex_lock(mutex)) {
            printf("error3\n");
        }
        printf("parent do second.\n");
        if (0 != pthread_mutex_unlock(mutex)) {
            printf("error4\n");
        }
    } else {
        // 
    }
}
