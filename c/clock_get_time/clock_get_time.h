#ifndef __C_CLOCK_GET_TIME_H__
#define __C_CLOCK_GET_TIME_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

void clock_gettime_begin(int flag);
uint64_t clock_gettime_end(int flag, int print);

#ifdef __cplusplus
};
#endif

#endif
