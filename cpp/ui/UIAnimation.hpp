#pragma once

#include <string>
extern "C"
{
#include "UIAnimation.h"
}

namespace UI
{
    template <class T>
    class Animation
    {
    public:
        static UIAnimation create(int duration, const char *key, float (*timingFunction)(float t), T startValue, T endValue)
        {
            T _startValue = startValue;
            T _endValue = endValue;
            UIAnimation anim;

            anim.finished = 0;
            anim.forKey = key;
            anim.timingFunction = timingFunction;
            anim.startValue = &_startValue;
            anim.endValue = &_endValue;
            anim.startTime = UIAnimationGetCurrentTime();
            anim.endTime = UIAnimationGetCurrentTime() + duration;
            anim._valueSize = sizeof(T);
            anim.duration = duration;

            return UIAnimationCopy(anim);
        }
    };
};