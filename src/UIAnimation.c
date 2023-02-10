#include "UIAnimation.h"
#include <time.h>
#include <stdint.h>
#include <string.h>

uint64_t UIAnimationGetCurrentTime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return (uint64_t)(ts.tv_sec) * 1000 + (uint64_t)(ts.tv_nsec) / 1000000;
}

UIAnimation UIAnimationCopy(UIAnimation anim)
{
    UIAnimation copy = anim;
    copy.startValue = calloc(1, sizeof(anim._valueSize));
    copy.endValue = calloc(1, sizeof(anim._valueSize));
    memcpy(copy.startValue, anim.startValue, anim._valueSize);
    memcpy(copy.endValue, anim.endValue, anim._valueSize);
    return copy;
}

UIAnimation UIAnimationDestroy()
{
}