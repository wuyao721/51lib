#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("%ld\n", sysconf(_SC_THREAD_PROCESS_SHARED));
    return 0;
}
