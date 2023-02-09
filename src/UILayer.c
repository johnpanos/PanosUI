
#include <stdlib.h>
#include <string.h>
#include "UILayer.h"
#include "UIAnimation.h"

const char *kUILayerKeyPositionX = "position.x";
const char *kUILayerKeyPositionY = "position.y";

const char *kUILayerKeyBoundsWidth = "bounds.width";
const char *kUILayerKeyBoundsHeight = "bounds.height";

const char *kUILayerKeyBackgroundColor = "backgroundColor";

const char *kUILayerKeyBorderWidth = "borderWidth";
const char *kUILayerKeyBorderColor = "borderColor";

const char *kUILayerKeyShadowOffset = "shadowOffset";
const char *kUILayerKeyShadowColor = "shadowColor";
const char *kUILayerKeyShadowRadius = "shadowRadius";

const char *kUILayerKeyOpacity = "opacity";

#define KEY_EQUAL(anim, str) strcmp(anim->forKey, str) == 0
#define VALUE_FOR_TYPE(anim, type, prop) *((type *)anim->prop)

float lerp(float a, float b, float t)
{
    return a + (t * (b - a));
}

UILayer *UILayerCreate(UIRect frame, UIRect bounds)
{
    UILayer *layer = calloc(1, sizeof(UILayer));
    layer->frame = frame;
    layer->bounds = bounds;
    layer->animations = ArrayCreate(sizeof(UIAnimation *));
    return layer;
}

void UILayerAddSublayer(UILayer *layer, UILayer *sublayer)
{
    ArrayAddValue(layer->sublayers, sublayer);
}

UILayer UILayerGetInFlight(UILayer layer)
{
    UILayer copied = layer;

    for (int i = 0; i < ArrayGetCapacity(copied.animations); i++)
    {
        UIAnimation *anim = ArrayGetValueAtIndex(copied.animations, i);

        uint64_t now = UIAnimationGetCurrentTime();
        int deltaT = now - anim->startTime;
        printf("dT: %d\n", deltaT);
        float progress = (float)deltaT / (float)anim->duration;

        printf("now  %"PRIu64"\n", now);
        printf("progress %f\n", progress);

        if (KEY_EQUAL(anim, kUILayerKeyBackgroundColor))
        {
            UIColor bg = VALUE_FOR_TYPE(anim, UIColor, startValue);
            copied.backgroundColor = bg;
        }
        else if (KEY_EQUAL(anim, kUILayerKeyBorderColor))
        {
            UIColor bc = VALUE_FOR_TYPE(anim, UIColor, startValue);
            copied.borderColor = bc;
        }
        else if (KEY_EQUAL(anim, kUILayerKeyBorderWidth))
        {
            float bw = VALUE_FOR_TYPE(anim, float, startValue);
            copied.borderWidth = bw;
        }
        else if (KEY_EQUAL(anim, kUILayerKeyBoundsHeight))
        {
        }
        else if (KEY_EQUAL(anim, kUILayerKeyBoundsWidth))
        {
        }
        else if (KEY_EQUAL(anim, kUILayerKeyOpacity))
        {
            copied.opacity = lerp(
                VALUE_FOR_TYPE(anim, float, startValue),
                VALUE_FOR_TYPE(anim, float, endValue),
                progress);
        }
        else if (KEY_EQUAL(anim, kUILayerKeyPositionX))
        {
        }
        else if (KEY_EQUAL(anim, kUILayerKeyPositionY))
        {
        }
        else if (KEY_EQUAL(anim, kUILayerKeyShadowColor))
        {
        }
        else if (KEY_EQUAL(anim, kUILayerKeyShadowOffset))
        {
        }
        else if (KEY_EQUAL(anim, kUILayerKeyShadowRadius))
        {
        }
        else
        {
            printf("No animation serializer found for key: %s\n", anim->forKey);
        }
    }

    return copied;
}