#pragma once
#include <stdint.h>
#include <sys/types.h>

typedef struct _UIAnimation
{
    int finished;

    const char* forKey;
    int duration;

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