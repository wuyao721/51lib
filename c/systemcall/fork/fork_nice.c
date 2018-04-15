#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    nice(1);

    if(0 == fork()){
        printf("nice: %d\n", nice(0));
        return 0;
    }else {
        printf("nice: %d\n", nice(0));
        return 0;
    }
    return 0;
}
