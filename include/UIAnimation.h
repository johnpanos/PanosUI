#pragma once
#include <stdint.h>
#include <sys/types.h>

typedef struct _UIAnimation
{
    int finished;

    const char* forKey;
    int duration;
    float (*timingFunction)(float t);

    void *startValue;
    void *endValue;
    size_t _valueSize;

    uint64_t startTime;
    uint64_t endTime;
} UIAnimation;

typedef struct _UITransaction UITransaction;

uint64_t UIAnimationGetCurrentTime();

UIAnimation UIAnimationCopy(UIAnimation anim);

void UIAnimationTransactionBegin();
void UIAnimationTransactionSetDuration();
void UIAnimationTransactionEnd();
void UIAnimationTransactionFlush();

void UIAnimationCoreTick();

// MARK: Easing functions
float UIAnimationTimingFunctionLinear(float t);
float UIAnimationTimingFunctionEaseInSine(float t);
float UIAnimationTimingFunctionEaseOutSine(float t);
float UIAnimationTimingFunctionEaseInOutSine(float t);
float UIAnimationTimingFunctionEaseInQuad(float t);
float UIAnimationTimingFunctionEaseOutQuad(float t);
float UIAnimationTimingFunctionEaseInOutQuad(float t);
float UIAnimationTimingFunctionEaseInCubic(float t);
float UIAnimationTimingFunctionEaseOutCubic(float t);
float UIAnimationTimingFunctionEaseInOutCubic(float t);
float UIAnimationTimingFunctionEaseInQuart(float t);
float UIAnimationTimingFunctionEaseOutQuart(float t);
float UIAnimationTimingFunctionEaseInOutQuart(float t);
float UIAnimationTimingFunctionEaseInQuint(float t);
float UIAnimationTimingFunctionEaseOutQuint(float t);
float UIAnimationTimingFunctionEaseInOutQuint(float t);
float UIAnimationTimingFunctionEaseInExpo(float t);
float UIAnimationTimingFunctionEaseOutExpo(float t);
float UIAnimationTimingFunctionEaseInOutExpo(float t);
float UIAnimationTimingFunctionEaseInCirc(float t);
float UIAnimationTimingFunctionEaseOutCirc(float t);
float UIAnimationTimingFunctionEaseInOutCirc(float t);
float UIAnimationTimingFunctionEaseInBack(float t);
float UIAnimationTimingFunctionEaseOutBack(float t);
float UIAnimationTimingFunctionEaseInOutBack(float t);
float UIAnimationTimingFunctionEaseInElastic(float t);
float UIAnimationTimingFunctionEaseOutElastic(float t);
float UIAnimationTimingFunctionEaseInOutElastic(float t);
float UIAnimationTimingFunctionEaseInBounce(float t);
float UIAnimationTimingFunctionEaseOutBounce(float t);
float UIAnimationTimingFunctionEaseInOutBounce(float t);