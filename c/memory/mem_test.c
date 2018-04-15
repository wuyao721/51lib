//gcc -g -O2 mem_test.c
#include "mm_memcpy.h"
#include <stdio.h>
#include <sys/time.h>

char buf1[1048576];
char buf2[1048576];

int array[] = {
    16, 64, 256, 1024, 4096, 16384, 65536, 262144//, 1048576
};

void printime(int size, int cnt, void func(int size, int cnt))
{
    struct timeval tv1;
    struct timeval tv2;
    struct timezone tz;

    gettimeofday(&tv1, &tz);
    func(size, cnt);
    gettimeofday(&tv2, &tz);
    printf("interval sec: %d, usec: %d\n", tv2.tv_sec - tv1.tv_sec, tv2.tv_usec - tv1.tv_usec);
}

void memcpy_test(int size, int cnt) 
{
    int i;
    for (i = 0; i < cnt; i++) {
        memcpy(buf1, buf2, size);
    }
}

void rte_memcpy_test(int size, int cnt) 
{
    int i;
    for (i = 0; i < cnt; i++) {
        rte_memcpy(buf1, buf2, size);
    }
}

int main()
{
    int cnt = 10000 * 100;
    int i;

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    for (i = 0; i < sizeof(array) / sizeof(int); i++) {
        printf("memcpy test. size: %d cnt: %d:\n", array[i], cnt);
        printf("    memcpy ");
        printime(array[i], cnt, memcpy_test);
        printf("rte_memcpy ");
        printime(array[i], cnt, rte_memcpy_test);
        printf("\n");
    }
    return 0; 
}
