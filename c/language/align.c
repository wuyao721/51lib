//gcc align.c && ./a.out
#include <stdio.h>
#include <stdint.h>

#pragma pack(1)
typedef struct _eth_hdr1 {
    union
    {
        struct
        {
            uint8_t   dst[6];
            uint8_t   src[6];
        }mac;
        struct
        {
            union
            {
                uint32_t a;
            };
        };
    };
    uint16_t  eth_type;     /* packet type ID field */
} eth_hdr1;
typedef struct _eth_hdr2 {
    union
    {
        struct
        {
            uint8_t   dst[6];
            uint8_t   src[6];
        }mac;
        struct
        {
            union
            {
                uint64_t a;
            };
        };
    };
    uint16_t  eth_type;     /* packet type ID field */
} eth_hdr2;
#pragma pack()

typedef struct _eth_hdr3 {
    union
    {
        struct
        {
            uint8_t   dst[6];
            uint8_t   src[6];
        }mac;
        struct
        {
            union
            {
                uint32_t a;
            };
        };
    };
    uint16_t  eth_type;     /* packet type ID field */
} eth_hdr3;
typedef struct _eth_hdr4 {
    union
    {
        struct
        {
            uint8_t   dst[6];
            uint8_t   src[6];
        }mac;
        struct
        {
            union
            {
                uint64_t a;
            };
        };
    };
    uint16_t  eth_type;     /* packet type ID field */
} eth_hdr4;

int main()
{
    printf("sizeof(eth_hdr1): %d\n", (int) sizeof(eth_hdr1));
    printf("sizeof(eth_hdr2): %d\n", (int) sizeof(eth_hdr2));
    printf("sizeof(eth_hdr3): %d\n", (int) sizeof(eth_hdr3));
    printf("sizeof(eth_hdr4): %d\n", (int) sizeof(eth_hdr4));

    return 0;
}
