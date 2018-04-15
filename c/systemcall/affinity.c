#define _GNU_SOURCE
#include <sched.h>

int set_taffinity(pid_t pid,int nCpuNum)
{
	cpu_set_t mask;

	CPU_ZERO(&mask);
    CPU_SET(nCpuNum, &mask);
    if (sched_setaffinity(pid, sizeof(mask), &mask) == -1) {
        return -1;
    }
    return 0;
}

int main()
{
    sleep(1);
    set_taffinity(0,47);
    while(1) {
        sleep(1);
    }
}
