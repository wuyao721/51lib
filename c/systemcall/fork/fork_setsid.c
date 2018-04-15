#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    char *buf[128];

    if(0 == fork()){
        const char *a = "child\n";
        if (-1 == setsid()){
            printf("setsid error.\n");
        }
        memcpy(buf, a, strlen(a)+1);
        write(3, (void *)buf, strlen(a));
        write(1, (void *)buf, strlen(a));
        while(1) {
            sleep(1);
            return 0;
        }
        return 0;
    }else {
        const char *b = "parent\n";
        memcpy(buf, b, strlen(b)+1);
        write(3, (void *)buf, strlen(b));
        while(1) {
            sleep(1);
        }
        return 0;
    }

}
