#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef RES
void multi_add(int *restrict p1, int *restrict p2, int *restrict pi)
#else
void multi_add(int * p1, int * p2, int * pi)
#endif
{
    *p1 += *pi;
    *p2 += *pi;
}
int main()
{
    int a = 1, b = 2;
    int inc = 1;

    multi_add(&a, &b, &inc);
    
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
