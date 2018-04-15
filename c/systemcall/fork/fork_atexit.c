#include <stdio.h>
#include <stdlib.h>

void f()
{
    printf("f called.\n");
}

int main()
{
    atexit(f);

    if(0 == fork()){
        return 0;
    }else {
        return 0;
    }
    return 0;
}
