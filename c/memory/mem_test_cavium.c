
#include "cvmx-config.h"
#include "cvmx.h"
#include "cvmx-coremask.h"
#include "cvmx-bootmem.h"
#include "cvmx-sysinfo.h"

#include <stdio.h>
#include <sys/time.h>
#include <string.h>

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
    printf("interval sec: %d, usec: %d\n", (int)(tv2.tv_sec - tv1.tv_sec), (int)(tv2.tv_usec - tv1.tv_usec));
}

inline void memcpy_test(int size, int cnt) 
{
    int i;
    for (i = 0; i < cnt; i++) {
        memcpy(buf1, buf2, size);
    }
}

inline void cavium_memcpy_test(int size, int cnt) 
{
    int i;
    uint64_t *ptr1 = (uint64_t *) buf1;
    uint64_t *ptr2 = (uint64_t *) buf2;
    int num_cache_lines = size / 8;

    for (i = 0; i < cnt; i++) {
        ptr1 = (uint64_t *) buf1;
        ptr2 = (uint64_t *) buf2;
        num_cache_lines = size / 8;
        while(num_cache_lines-- > 0) {
            *ptr1++ = *ptr2++;
        }
    }
}

inline void buffer_init_fast(int size, int cnt)
{
    uint64_t num_cache_lines = size / 128;
    uint64_t *ptr1 = (uint64_t *) buf1;
    uint64_t *ptr2 = (uint64_t *) buf2;
    int i;
    for (i = 0; i < cnt; i++) {
        num_cache_lines = size / 128;
        ptr1 = (uint64_t *) buf1;
        ptr2 = (uint64_t *) buf2;
        while(num_cache_lines-- > 0) { // write one cache line at a time
            *ptr1++ = *ptr2++; // via 16 64-bit writes
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
            *ptr1++ = *ptr2++;
        };
    }
}

int main()
{
    int cnt = 10000 * 100;
    int i;

    if (cvmx_get_core_num() != 0) {
        return 0;
    }

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    printf("memcpy test. size: %d cnt: %d:\n", 4096, cnt);
    printf("     memcpy ");
    printime(4096, cnt, memcpy_test);
    printf("cvmx memcpy ");
    printime(4096, cnt, buffer_init_fast);
    printf("\n");

    for (i = 0; i < (int)(sizeof(array) / sizeof(int)); i++) {
        printf("memcpy test. size: %d cnt: %d:\n", array[i], cnt);
        printf("     memcpy ");
        printime(array[i], cnt, memcpy_test);
        printf("cvmx memcpy ");
        printime(array[i], cnt, cavium_memcpy_test);
        printf("\n");
    }
    return 0; 
}
