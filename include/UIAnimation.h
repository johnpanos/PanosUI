#pragma once
#include "UIGeometry.h"
#include <stdint.h>
#include <sys/types.h>

typedef struct _UIAnimation
{
	int finished;

	const char *forKey;
	int duration;
	UIFloat (*timingFunction)(UIFloat t);

	void *startValue;
	void *endValue;
	size_t _valueSize;

	uint64_t startTime;
	uint64_t endTime;
} UIAnimation;

typedef struct _UITransaction
{
	uint64_t duration;
	UIFloat (*timingFunction)(UIFloat t);

} UITransaction;

uint64_t UIAnimationGetCurrentTime();

UIAnimation UIAnimationCopy(UIAnimation anim);
void UIAnimationDestroy(UIAnimation anim);

void UIAnimationTransactionBegin();
void UIAnimationTransactionSetDuration(uint64_t duration);
void UIAnimationTransactionEnd();
void UIAnimationTransactionFlush();

void UIAnimationCoreTick();

// MARK: Easing functions
UIFloat UIAnimationTimingFunctionLinear(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInSine(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseOutSine(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInOutSine(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInQuad(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseOutQuad(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInOutQuad(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInCubic(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseOutCubic(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInOutCubic(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInQuart(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseOutQuart(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInOutQuart(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInQuint(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseOutQuint(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInOutQuint(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInExpo(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseOutExpo(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInOutExpo(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInCirc(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseOutCirc(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInOutCirc(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInBack(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseOutBack(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInOutBack(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInElastic(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseOutElastic(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInOutElastic(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInBounce(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseOutBounce(UIFloat t);
UIFloat UIAnimationTimingFunctionEaseInOutBounce(UIFloat t);