#include "UIAnimation.h"
#include <time.h>

uint64_t UIAnimationGetCurrentTime()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    return (now.tv_sec * 1000) + (now.tv_nsec / 1000);
}