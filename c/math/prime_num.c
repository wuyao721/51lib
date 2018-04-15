#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>


void prime_in_range(uint32_t min, uint32_t max)
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t value = 0;

    for (i = min; i <= max; i++) {
        value = (uint32_t)sqrt(i);
        for (j = 2; j <= value; j++) {
            if (i % j == 0) {
                break;
            }
        }
        if (j > value) {
            printf("%d\n", i);
        }
        
    }
}

int main()
{
    prime_in_range(1, 1000);
    return 0;
}
