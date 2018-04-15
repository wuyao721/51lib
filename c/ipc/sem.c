#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
    int semget(0x1234, 3, int semflg);
    return 0;
}
