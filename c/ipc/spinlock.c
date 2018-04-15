
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <crypt.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <time.h>
#include <getopt.h>
#include <inttypes.h>
#include <alloca.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <sys/mman.h>
#include <sys/stat.h>

pthread_spinlock_t *g_ptr = NULL;

int shared_memory_init()
{  
    char   *ptr      = NULL;
    size_t size      = 0;

    size = sizeof(pthread_spinlock_t);

    if( MAP_FAILED == (ptr = (char*)mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1,0))) { 
        return -1;
    }

    g_ptr = (pthread_spinlock_t *) ptr;

    if (0 != pthread_spin_init(g_ptr, PTHREAD_PROCESS_SHARED)) {
        return -1;
    }

    return 0;
}


int main()
{
    shared_memory_init();
    pid_t a = fork();
    int ret;
    if (a == 0) {
        //ret = pthread_spin_lock(g_ptr);
        printf("child ret: %d\n", ret);
        while(1) {
            sleep(1);
            //pthread_spin_unlock(g_conf.loglock);
        }
    } else {
        while(1) {
            sleep(1);
            ret = pthread_spin_lock(g_ptr);
            printf("father ret: %d\n", ret);
            sleep(1);
            ret = pthread_spin_unlock(g_ptr);
            printf("father ret2: %d\n", ret);
        }
        
    }
}
