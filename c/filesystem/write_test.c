//gcc write_test.c -o write_test
#define _GNU_SOURCE
#include <sched.h>

#include <stdio.h>

int main()
{
    pid_t pid = getpid();
	cpu_set_t mask;
	CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if (sched_setaffinity(pid, sizeof(mask), &mask) == -1)
    {
        printf("sched_setaffinity false.\n");
        return -1;
    }

    char buf[1096000];
    FILE *fp = fopen("a.txt", "wb");
    if (NULL == fp)
    {
        printf("fopen false.\n");
        return -1;
    }

    memset(buf, 0, sizeof(buf));
    while(1) {
        fwrite(buf, sizeof(buf), 1, fp);
    }
    return 0;
}
