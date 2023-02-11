#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UILayer.h"
#include "UIAnimation.h"
#include "platform.h"

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

const char *kUILayerKeyCornerRadius = "cornerRadius";
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
    layer->animations = ArrayCreate(sizeof(UIAnimation));
    layer->sublayers = ArrayCreate(sizeof(UILayer *));
    layer->platformLayer = _UIPlatformLayerCreate();
    return layer;
}

void UILayerAddSublayer(UILayer *layer, UILayer *sublayer)
{
    ArrayAddValue(layer->sublayers, sublayer);
    _UIPlatformLayerAddSublayer(layer, sublayer);
}

void UILayerRemoveSublayer(UILayer *layer, UILayer *sublayer)
{
    ArrayRemoveValueByRef(layer->sublayers, sublayer);
    _UIPlatformLayerRemoveSublayer(layer, sublayer);
}

void UILayerAddAnimation(UILayer *layer, UIAnimation anim)
{
    UIAnimation *copiedAnim = calloc(1, sizeof(UIAnimation));
    *copiedAnim = UIAnimationCopy(anim);
    ArrayAddValue(layer->animations, copiedAnim);
}

UILayer UILayerGetInFlight(UILayer layer)
{
    UILayer copied = layer;

    for (int i = 0; i < ArrayGetCapacity(copied.animations); i++)
    {
        UIAnimation *anim = ArrayGetValueAtIndex(copied.animations, i);

        uint64_t now = UIAnimationGetCurrentTime();
        int deltaT = now - anim->startTime;
        float prog = (float)deltaT / (float)anim->duration;
        float progress = anim->timingFunction(prog);

        if (prog >= 1)
        {
            progress = 1.0f;
            anim->finished = 1;
        }
        else if (prog <= 0)
        {
            progress = 0.0f;
            anim->finished = 0;
        }

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
            copied.frame.height = (int)lerp(
                VALUE_FOR_TYPE(anim, int, startValue),
                VALUE_FOR_TYPE(anim, int, endValue),
                progress);
        }
        else if (KEY_EQUAL(anim, kUILayerKeyBoundsWidth))
        {
            copied.frame.width = (int)lerp(
                VALUE_FOR_TYPE(anim, int, startValue),
                VALUE_FOR_TYPE(anim, int, endValue),
                progress);
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
            copied.frame.x = (int)lerp(
                VALUE_FOR_TYPE(anim, int, startValue),
                VALUE_FOR_TYPE(anim, int, endValue),
                progress);
        }
        else if (KEY_EQUAL(anim, kUILayerKeyPositionY))
        {
            copied.frame.y = (int)lerp(
                VALUE_FOR_TYPE(anim, int, startValue),
                VALUE_FOR_TYPE(anim, int, endValue),
                progress);
        }
        else if (KEY_EQUAL(anim, kUILayerKeyShadowColor))
        {
        }
        else if (KEY_EQUAL(anim, kUILayerKeyShadowOffset))
        {
        }
        else if (KEY_EQUAL(anim, kUILayerKeyShadowRadius))
        {
            copied.shadowRadius = lerp(
                VALUE_FOR_TYPE(anim, float, startValue),
                VALUE_FOR_TYPE(anim, float, endValue),
                progress);
        }
        else if (KEY_EQUAL(anim, kUILayerKeyCornerRadius))
        {
            copied.cornerRadius = lerp(
                VALUE_FOR_TYPE(anim, float, startValue),
                VALUE_FOR_TYPE(anim, float, endValue),
                progress);
        }
        else
        {
            printf("No animation serializer found for key: %s\n", anim->forKey);
        }
    }

    Array animsToDelete = ArrayCreate(sizeof(UIAnimation *));
    for (int i = 0; i < ArrayGetCapacity(layer.animations); i++)
    {
        UIAnimation *anim = ArrayGetValueAtIndex(layer.animations, i);
        if (anim->finished)
        {
            ArrayAddValue(animsToDelete, anim);
        }
    }

    for (int i = 0; i < ArrayGetCapacity(animsToDelete); i++)
    {
        UIAnimation *anim = ArrayGetValueAtIndex(animsToDelete, i);
        ArrayRemoveValueByRef(layer.animations, anim);
        free(anim);
    }
    ArrayDestroy(animsToDelete);

    return copied;
}

void UILayerRenderInContext(UILayer *layer, UIGraphicsContext *context)
{
    if (layer->clipToBounds)
    {
        UIGraphicsContextClipToRect(context, layer->frame, layer->cornerRadius);
    }

    if (layer->shadowColor.a > 0)
    {
        UIGraphicsContextSave(context);
        {
            UIGraphicsContextSetShadow(context, layer->shadowOffset, layer->shadowRadius);
            UIGraphicsSetFillColor(context, layer->shadowColor);
            UIGraphicsContextAddRect(context, layer->frame, layer->cornerRadius);
        }
        UIGraphicsContextRestore(context);
    }

    UIGraphicsSetFillColor(context, layer->backgroundColor);
    UIGraphicsContextAddRect(context, layer->frame, layer->cornerRadius);

    if (layer->borderWidth > 0)
    {
        UIGraphicsSetStrokeColor(context, layer->borderColor);
        UIGraphicsSetStrokeWidth(context, layer->borderWidth);
        UIGraphicsContextAddRect(context, layer->frame, layer->cornerRadius);
    }
}