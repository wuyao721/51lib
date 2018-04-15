#include <stdio.h>

int c();
#ifdef __cplusplus
extern "C"
{
#endif
int b2()
{
    printf("b2 fun call.\n");
}

#ifdef __cplusplus
}
#endif

int b()
{
    printf("b fun call.\n");
    b2();
}
