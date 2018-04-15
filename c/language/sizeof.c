#include <stdio.h>
#include <stdint.h>

#pragma pack(8)

typedef struct flow_stat_
{
    uint32_t packets;
    uint64_t octets;
} flow_stat_t;

typedef struct rule_1 
{
    uint16_t port;
    uint8_t  proto;
    uint8_t  action;
    //uint8_t  mac[6];
    //uint32_t rule_id;
    //uint8_t  priority;
    flow_stat_t hits;
    uint16_t  mark;
} rule_1_t;

typedef struct rule_2
{
    uint16_t port;
    uint8_t  proto;
    uint8_t  action;
    //uint8_t  mac[6];
    //uint32_t rule_id;
    //uint8_t  priority;
    uint16_t  mark;
    flow_stat_t hits;
} rule_2_t;

typedef struct rule_3
{
    uint16_t port;
    uint8_t  proto;
    uint8_t  action;
    //uint8_t  mac[6];
    //uint32_t rule_id;
    //uint8_t  priority;
    uint16_t  mark;
    uint32_t packets;
    uint64_t octets;
} rule_3_t;

typedef struct rule_4
{
    uint16_t port;
    uint8_t  proto;
    uint8_t  action;
    //uint8_t  mac[6];
    //uint32_t rule_id;
    //uint8_t  priority;
    uint32_t packets;
    uint64_t mark:16;
    uint64_t octets:38;
} rule_4_t;

#pragma pack()


struct k{
    int a;
    short b;
    long c;
    char d;
};

int main()
{
    printf("sizeof(rule_1_t): %d\n", sizeof(rule_1_t));
    printf("sizeof(rule_2_t): %d\n", sizeof(rule_2_t));
    printf("sizeof(rule_3_t): %d\n", sizeof(rule_3_t));
    printf("sizeof(rule_4_t): %d\n", sizeof(rule_4_t));
    printf("sizeof: %d\n", sizeof(struct k));

    int a = 1234556;
    short b = a;
    return b;
}
