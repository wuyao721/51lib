#include <stdio.h>
#include <time.h>

// CST China Standard Time
// UTC Universal Time  Cordonn&Eacute
// GMT Greenwich Mean Time
// EST Eastern Standard Time

int main()
{
    char buf[128];
    time_t t = time(NULL);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S (%Z)", localtime(&t));
    printf("current time: %s\n", buf);
    return 0;
}
