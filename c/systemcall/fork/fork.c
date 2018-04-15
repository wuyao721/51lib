#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>

int main()
{
    pid_t pid;

    if (0 == (pid = fork())) {
        while(1) {
            sleep(1);
        }
    } else if (pid > 0) {
        return 0; 
    } else {
        // 
    }
}
