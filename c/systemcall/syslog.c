#include <syslog.h>

int main()
{
    syslog(LOG_ERR, "this is a test from syslog.c");
    return 0;
}
