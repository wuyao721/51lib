#include "clock_get_time.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C"
{
#endif

static struct timespec s_tp;
static int             s_status = 0;
static int             s_sec = 30;
static uint64_t        s_count = 0;
static uint64_t        s_max_interval = 0;
static uint64_t        s_total_interval = 0;
static time_t          s_last = 0;

void clock_gettime_begin(int flag)
{
    if (flag) {
        s_status = 0;
        if (0 == clock_gettime(CLOCK_REALTIME, &s_tp)) {
            s_status = 1;
            if (s_last == 0) {
                s_last = s_tp.tv_sec;
            }
        }
    }
}

uint64_t clock_gettime_end(int flag, int print)
{
    struct timespec tp;
    uint64_t interval;

    if (s_status == 1 && flag) {
        if (0 == clock_gettime(CLOCK_REALTIME, &tp)) {
            s_status = 0;
            interval = (uint64_t)((tp.tv_sec - s_tp.tv_sec) * 1000000000 + (tp.tv_nsec - s_tp.tv_nsec));
            s_total_interval += interval;
            s_max_interval = (interval > s_max_interval) ? interval : s_max_interval;
            s_count++;
            if (print) {
                printf("Longest Time. %dst pkt. max(ms): %-8lu average(ns): %-8lu\n",
                   s_count, s_max_interval/1000, s_total_interval/s_count);
            }
            if (tp.tv_sec - s_last > s_sec) {
                s_last = tp.tv_sec;
                printf("Longest Time. call pps: %-8lu max(ms): %-8lu average(ns): %-8lu\n",
                      s_count/30, s_max_interval/1000, s_total_interval/s_count);
                s_count = 0;
                s_total_interval = 0;
                s_max_interval = 0;
            }
            return interval;
        }
    }
    return 0;
}

long clock_gettime_resolution()
{
    struct timespec res;
    if (0 == clock_getres(CLOCK_REALTIME, &res)) {
        return res.tv_nsec;
    }

    return 0;
}

#ifdef __cplusplus
}
#endif
