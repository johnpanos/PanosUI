#include "UIAnimation.h"
#include <time.h>
#include <stdint.h>

uint64_t UIAnimationGetCurrentTime() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return (uint64_t)(ts.tv_sec) * 1000 + (uint64_t)(ts.tv_nsec) / 1000000;
}