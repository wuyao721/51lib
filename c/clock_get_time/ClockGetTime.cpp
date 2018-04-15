#include "ClockGetTime.h"
#include "clock_get_time.h"
#include <stdio.h>
#include <unistd.h>

ClockGetTime::ClockGetTime() 
{
    mStatus = 0;
    mTp.tv_sec = 0;
    mTp.tv_nsec = 0;
    mSec = 30;
    mMaxInterval = 0;
    mTotalInterval = 0;
    mCount = 0;
    mLast = 0;
    Begin(1);
}

ClockGetTime::~ClockGetTime() 
{
    End(1);
}

void ClockGetTime::Begin(int flag)
{
    if (flag) {
        mStatus = 0;
        if (0 == clock_gettime(CLOCK_REALTIME, &mTp)) {
            mStatus = 1;
            if (mLast == 0) {
                mLast = mTp.tv_sec;
            }
        }
    }
}

uint64_t ClockGetTime::End(int flag)
{
    struct timespec tp;
    uint64_t interval;

    if (mStatus == 1 && flag) {
        if (0 == clock_gettime(CLOCK_REALTIME, &tp)) {
            mStatus = 0;
            interval = (uint64_t)((tp.tv_sec - mTp.tv_sec) * 1000000000 + (tp.tv_nsec - mTp.tv_nsec));
            mTotalInterval += interval;
            mMaxInterval = (interval > mMaxInterval) ? interval : mMaxInterval;
            mCount++;
                printf("Longest Time. %dst pkt. max(ms): %-8lu average(ns): %-8lu\n",
                      mCount, mMaxInterval/1000, mTotalInterval/mCount);
            if (tp.tv_sec - mLast > 30) {
                mLast = tp.tv_sec;
                printf("Longest Time. call pps: %-8lu max(ms): %-8lu average(ns): %-8lu\n",
                      mCount/30, mMaxInterval/1000, mTotalInterval/mCount);
                mCount = 0;
                mTotalInterval = 0;
                mMaxInterval = 0;
            }
            return interval;
        }
    }
    return 0;
}

long ClockGetTime::GetResolution()
{
    struct timespec res;
    if (0 == clock_getres(CLOCK_REALTIME, &res)) {
        return res.tv_nsec;
    }

    return 0;
}

ClockGetTime &ClockGetTime::GetInstance()
{
    static ClockGetTime *instance = NULL;
    if (instance == NULL) {
        instance = new ClockGetTime();
    }
    return *instance;
}

