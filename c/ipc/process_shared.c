#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>

void process_proc()
{

}

int main()
{
    pid_t pid;
    volatile int *buf1;
    if (MAP_FAILED == (buf1 = (int *)mmap(NULL, sizeof(int)*2, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0))) {
        perror("mmap");
        return -1;
    }
    
    buf1[0] = 0x11;
    buf1[1] = 0x11;

    volatile int *buf = (int *)buf1;
    if (0 == (pid = fork())) {
        while(1){
            if (buf[0] == 0x22) {
                if (buf[1] == 0x11){
                    printf("buf[1] == 1\n");
                }/*else {
                    printf("ok1.\n");
                    }*/
                buf[1] = 0x11;
                buf[0] = 0x11;
            } else {
                ;  
            }
        } 
    } else if (pid > 0) {
        while(1){
            if (buf[0] == 0x11) {
                if (buf[1] == 0x22){
                    printf("buf[1] == 0\n");
                }/*else {
                    printf("ok2.\n");
                    }*/
                buf[1] = 0x22;
                buf[0] = 0x22;
            } else {
                ;  
            }
        } 
    } else {
        // 
    }
}
