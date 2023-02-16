#include "UIAnimation.h"
#include "shared/Array.h"
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

void UIAnimationDestroy(UIAnimation anim)
{
    free(anim.startValue);
    free(anim.endValue);
}

typedef struct _UIAnimationData
{
    Array transactions;
} UIAnimationData;

UIAnimationData ANIM_DATA;

void UIAnimationTransactionBegin()
{
    UITransaction *parentTransaction = ArrayGetValueAtIndex(
        ANIM_DATA.transactions,
        ArrayGetCapacity(ANIM_DATA.transactions) - 1);

    UITransaction *transaction = calloc(1, sizeof(UITransaction));
    memcpy(transaction, parentTransaction, sizeof(UITransaction));

    ArrayAddValue(ANIM_DATA.transactions, transaction);
}

void UIAnimationTransactionSetDuration(uint64_t duration)
{
    UITransaction *transaction = ArrayGetValueAtIndex(
        ANIM_DATA.transactions,
        ArrayGetCapacity(ANIM_DATA.transactions) - 1);

    if (transaction == NULL)
    {
        return;
    }

    transaction->duration = duration;
}

void UIAnimationTransactionEnd()
{
}

void UIAnimationTransactionFlush()
{
}

void UIAnimationCoreTick();