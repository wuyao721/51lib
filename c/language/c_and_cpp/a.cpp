#include <stdio.h>
int b();

#ifdef __cplusplus
extern "C"
{
#endif
int c();

#ifdef __cplusplus
}
#endif

int main()
{
    b();
    c();
    return 0;
}
//gcc -c a.cpp && gcc -c c.c && g++ -c b.cpp && g++ -o a.out a.o b.o c.o
