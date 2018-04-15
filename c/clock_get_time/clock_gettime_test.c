#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "clock_get_time.h"
#include <sys/time.h>

void clock_gettime_test()
{
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
}

void time_test()
{
    time(0);
}

void gettimeofday_test()
{
    gettimeofday(NULL, NULL);
}

// volatile ++ 100 times
void volatile_test() 
{
    volatile int a = 0;
    a++;a++;a++;a++;a++;a++;a++;a++;a++;a++; a++;a++;a++;a++;a++;a++;a++;a++;a++;a++;
    a++;a++;a++;a++;a++;a++;a++;a++;a++;a++; a++;a++;a++;a++;a++;a++;a++;a++;a++;a++;
    a++;a++;a++;a++;a++;a++;a++;a++;a++;a++; a++;a++;a++;a++;a++;a++;a++;a++;a++;a++;
    a++;a++;a++;a++;a++;a++;a++;a++;a++;a++; a++;a++;a++;a++;a++;a++;a++;a++;a++;a++;
    a++;a++;a++;a++;a++;a++;a++;a++;a++;a++; a++;a++;a++;a++;a++;a++;a++;a++;a++;a++;
}

void fopen_test()
{
    FILE *fp = fopen("/etc/profile", "rb");
}

void fopen_fclose_test()
{
    FILE *fp = fopen("/etc/rc.local", "rb");
    if (fp) fclose(fp);
}

void usleep_test()
{
    usleep(1);
}

void nanosleep_test()
{
    struct timespec req = {0, 1};
    nanosleep(&req, NULL);
}

void malloc_test()
{
    char *a;
    if (NULL != (a = (char *)malloc(4096))) {
        memset (a, 0, 4096);
    }
}

void malloc_memset_test()
{
    char *a;
    if (NULL != (a = (char *)malloc(4096))) {
        memset (a, 0, 4096);
    }
}

void malloc_free_test()
{
    char *a;
    if (NULL != (a = (char *)malloc(4096))) {
        free(a);
    }
}

typedef void (*callback)();

typedef struct testsuit
{
    char *name;
    callback cb;
}testsuit_t;

testsuit_t array[] =
{
    {"time", time_test},
    {"gettimeofday", gettimeofday_test},
    {"volatile ++ 100 times", volatile_test},
    {"fopen", fopen_test},
    {"fopen fclose", fopen_fclose_test},
    {"usleep 1 microsec", usleep_test},
    {"nanosleep 1 nanosec", nanosleep_test},
    {"malloc 4096", malloc_test},
    {"malloc 4096 memset", malloc_memset_test},
    {"malloc 4096 free", malloc_free_test},
    {"clock_gettime", clock_gettime_test},
};

int main()
{
    int i;
    uint64_t interval;
    for (i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        clock_gettime_begin(1);
        //clock_gettime_test();
        array[i].cb();
        //struct timespec tp;
        //clock_gettime(CLOCK_REALTIME, &tp);

        interval = clock_gettime_end(1, 0);
        printf("%2dst test. %30s: comsume %lu nanosecond.\n", i, array[i].name, interval);
    }
    return 0;
}
