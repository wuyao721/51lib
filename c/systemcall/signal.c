#include <signal.h>
#include <string.h>

void sig_handler(int sig)
{
    switch (sig) {
        case SIGTERM:
            break;
        case SIGCHLD:
            break;
        default:
            ;
    }
}

int main()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = sig_handler;
    sa.sa_flags = SA_INTERRUPT;
    sigaction(SIGTERM, &sa, NULL);
    
    return 0;
}
