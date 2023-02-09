#pragma once

typedef struct _UIAnimation
{
    int duration;
    float(easingFunc)(int progress);
    void *(lerp)(int progress, void *startValue, void *endValue);
    void *startValue;
    void *endValue;
} UIAnimation;

typedef struct _UITransaction UITransaction;

void UIAnimationTransactionBegin();
void UIAnimationTransactionSetDuration();
void UIAnimationTransactionEnd();
void UIAnimationTransactionFlush();

void UIAnimationCoreTick();