#include "UIAnimation.h"
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

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

float UIAnimationTimingFunctionLinear(float p)
{
    return p;
}

float UIAnimationTimingFunctionEaseInQuad(float p)
{
    return p * p;
}

float UIAnimationTimingFunctionEaseOutQuad(float p)
{
    return -(p * (p - 2));
}

float UIAnimationTimingFunctionEaseInOutQuad(float p)
{
    if (p < 0.5)
    {
        return 2 * p * p;
    }
    else
    {
        return (-2 * p * p) + (4 * p) - 1;
    }
}

float UIAnimationTimingFunctionEaseInCubic(float p)
{
    return p * p * p;
}

float UIAnimationTimingFunctionEaseOutCubic(float p)
{
    float f = (p - 1);
    return f * f * f + 1;
}

float UIAnimationTimingFunctionEaseInOutCubic(float p)
{
    if (p < 0.5)
    {
        return 4 * p * p * p;
    }
    else
    {
        float f = ((2 * p) - 2);
        return 0.5 * f * f * f + 1;
    }
}

float UIAnimationTimingFunctionEaseInQuart(float p)
{
    return p * p * p * p;
}

float UIAnimationTimingFunctionEaseOutQuart(float p)
{
    float f = (p - 1);
    return f * f * f * (1 - p) + 1;
}

float UIAnimationTimingFunctionEaseInOutQuart(float p)
{
    if (p < 0.5)
    {
        return 8 * p * p * p * p;
    }
    else
    {
        float f = (p - 1);
        return -8 * f * f * f * f + 1;
    }
}

float UIAnimationTimingFunctionEaseInQuint(float p)
{
    return p * p * p * p * p;
}

float UIAnimationTimingFunctionEaseOutQuint(float p)
{
    float f = (p - 1);
    return f * f * f * f * f + 1;
}

float UIAnimationTimingFunctionEaseInOutQuint(float p)
{
    if (p < 0.5)
    {
        return 16 * p * p * p * p * p;
    }
    else
    {
        float f = ((2 * p) - 2);
        return 0.5 * f * f * f * f * f + 1;
    }
}

float UIAnimationTimingFunctionEaseInSine(float p)
{
    return sin((p - 1) * M_PI_2) + 1;
}

float UIAnimationTimingFunctionEaseOutSine(float p)
{
    return sin(p * M_PI_2);
}

float UIAnimationTimingFunctionEaseInOutSine(float p)
{
    return 0.5 * (1 - cos(p * M_PI));
}

float UIAnimationTimingFunctionEaseInCirc(float p)
{
    return 1 - sqrt(1 - (p * p));
}

float UIAnimationTimingFunctionEaseOutCirc(float p)
{
    return sqrt((2 - p) * p);
}

float UIAnimationTimingFunctionEaseInOutCirc(float p)
{
    if (p < 0.5)
    {
        return 0.5 * (1 - sqrt(1 - 4 * (p * p)));
    }
    else
    {
        return 0.5 * (sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
    }
}

float UIAnimationTimingFunctionEaseInExpo(float p)
{
    return (p == 0.0) ? p : pow(2, 10 * (p - 1));
}

float UIAnimationTimingFunctionEaseOutExpo(float p)
{
    return (p == 1.0) ? p : 1 - pow(2, -10 * p);
}

float UIAnimationTimingFunctionEaseInOutExpo(float p)
{
    if (p == 0.0 || p == 1.0)
        return p;

    if (p < 0.5)
    {
        return 0.5 * pow(2, (20 * p) - 10);
    }
    else
    {
        return -0.5 * pow(2, (-20 * p) + 10) + 1;
    }
}

float UIAnimationTimingFunctionEaseInElastic(float p)
{
    return sin(13 * M_PI_2 * p) * pow(2, 10 * (p - 1));
}

float UIAnimationTimingFunctionEaseOutElastic(float p)
{
    return sin(-13 * M_PI_2 * (p + 1)) * pow(2, -10 * p) + 1;
}

float UIAnimationTimingFunctionEaseInOutElastic(float p)
{
    if (p < 0.5)
    {
        return 0.5 * sin(13 * M_PI_2 * (2 * p)) * pow(2, 10 * ((2 * p) - 1));
    }
    else
    {
        return 0.5 * (sin(-13 * M_PI_2 * ((2 * p - 1) + 1)) * pow(2, -10 * (2 * p - 1)) + 2);
    }
}

float UIAnimationTimingFunctionEaseInBack(float p)
{
    return p * p * p - p * sin(p * M_PI);
}

float UIAnimationTimingFunctionEaseOutBack(float p)
{
    float f = (1 - p);
    return 1 - (f * f * f - f * sin(f * M_PI));
}

float UIAnimationTimingFunctionEaseInOutBack(float p)
{
    if (p < 0.5)
    {
        float f = 2 * p;
        return 0.5 * (f * f * f - f * sin(f * M_PI));
    }
    else
    {
        float f = (1 - (2 * p - 1));
        return 0.5 * (1 - (f * f * f - f * sin(f * M_PI))) + 0.5;
    }
}

float UIAnimationTimingFunctionEaseInBounce(float p)
{
    return 1 - UIAnimationTimingFunctionEaseOutBounce(1 - p);
}

float UIAnimationTimingFunctionEaseOutBounce(float p)
{
    if (p < 4 / 11.0)
    {
        return (121 * p * p) / 16.0;
    }
    else if (p < 8 / 11.0)
    {
        return (363 / 40.0 * p * p) - (99 / 10.0 * p) + 17 / 5.0;
    }
    else if (p < 9 / 10.0)
    {
        return (4356 / 361.0 * p * p) - (35442 / 1805.0 * p) + 16061 / 1805.0;
    }
    else
    {
        return (54 / 5.0 * p * p) - (513 / 25.0 * p) + 268 / 25.0;
    }
}

float UIAnimationTimingFunctionEaseInOutBounce(float p)
{
    if (p < 0.5)
    {
        return 0.5 * UIAnimationTimingFunctionEaseInBounce(p * 2);
    }
    else
    {
        return 0.5 * UIAnimationTimingFunctionEaseOutBounce(p * 2 - 1) + 0.5;
    }
}
