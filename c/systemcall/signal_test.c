#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int g_a;
void sighandler(int sig)
{
    printf("sig: %d\n", sig);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = sighandler;
    sa.sa_flags = SA_INTERRUPT;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGCONT, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    int *k = (int *)malloc(12);
    int a = -1;
    char b = -1;
    short c = -1;
    unsigned int d  = (unsigned int)a;
    unsigned char e = -1;
    while(1){
        a++;
        a++;
        sleep(1);
    }
}
