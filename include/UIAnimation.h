#pragma once
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

typedef struct _UIAnimation
{
    char* forKey;
    int duration;
    void *startValue;
    void *endValue;

    uint64_t startTime;
    uint64_t endTime;
} UIAnimation;

typedef struct _UITransaction UITransaction;

uint64_t UIAnimationGetCurrentTime();

void UIAnimationTransactionBegin();
void UIAnimationTransactionSetDuration();
void UIAnimationTransactionEnd();
void UIAnimationTransactionFlush();

void UIAnimationCoreTick();