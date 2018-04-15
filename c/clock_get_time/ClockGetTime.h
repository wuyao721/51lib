#ifndef __CLOCK_GET_TIME_H__
#define __CLOCK_GET_TIME_H__

#include <time.h>
#include <stdint.h>

Class ClockGetTime
{
    struct timespec mTp;
    int mStatus;
    int mSec;
    uint64_t mCount;
    uint64_t mMaxInterval;
    uint64_t mTotalInterval;
    time_t mLast;
    
  public:
    ClockGetTime();
    ~ClockGetTime();
    long GetResolution();
    void Begin(int flag = 1);
    uint64_t End(int flag = 1);
    static ClockGetTime &GetInstance();
};

#endif
