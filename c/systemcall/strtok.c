#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    char buf[1024];
    char *str[] = {
        " ",
        "",
        "Ethernet1/0/12", 
        " Ethernet1/0/12 Vlan99   Ethernet1/0/24   ",};
    char *tok = NULL;
    int i;
    int j;
    char *saveptr;
    for (i = 0; i < sizeof(str)/sizeof(str[0]); i++) {
        strcpy(buf, str[i]);
        printf("%dst string is: %s\n", i, buf);
        if (NULL == (tok = strtok_r(buf, " \t", &saveptr))) {
            printf("    has no token.\n");
        } else {
            printf("    1st token: %s\n", tok);
            for (j = 2; NULL != (tok = strtok_r(NULL, " \t", &saveptr)); j++) {
                printf("    %dst token: %s\n", j, tok);
            }
        }
    }
    
    return 0;
}

