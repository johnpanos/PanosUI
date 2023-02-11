#pragma once

#include "shared/Array.h"
#include "UIRect.h"
#include "UIPoint.h"
#include "UIColor.h"
#include "UIGraphicsContext.h"
#include "UIAnimation.h"

// MARK: Layer Key Constants
extern const char *kUILayerKeyPositionX;
extern const char *kUILayerKeyPositionY;

extern const char *kUILayerKeyBoundsWidth;
extern const char *kUILayerKeyBoundsHeight;

extern const char *kUILayerKeyBackgroundColor;

extern const char *kUILayerKeyBorderWidth;
extern const char *kUILayerKeyBorderColor;

extern const char *kUILayerKeyShadowOffset;
extern const char *kUILayerKeyShadowColor;
extern const char *kUILayerKeyShadowRadius;

extern const char *kUILayerKeyCornerRadius;
extern const char *kUILayerKeyOpacity;

// MARK: Struct Defs
typedef struct _UIPlatformLayer UIPlatformLayer;
typedef struct _UILayer UILayer;
typedef struct _UILayer
{
    Array animations;
    Array sublayers;

    UILayer *parent;

    UIRect frame; // Calculated, never set
    UIRect bounds;

    UIColor backgroundColor;

    float borderWidth;
    UIColor borderColor;

    UIPoint shadowOffset;
    UIColor shadowColor;
    float shadowRadius;

    float opacity;

    float cornerRadius;
    int clipToBounds;

    UIGraphicsContext *ctx;

    UIPlatformLayer *platformLayer;
} UILayer;

UILayer *UILayerCreate(UIRect frame, UIRect bounds);
void UILayerDestroy(UILayer layer);

UIAnimation UILayerGetAnimationFor(UILayer *layer, const char *key, size_t valueSize, void *startValue, void *endValue);

void UILayerAddSublayer(UILayer *layer, UILayer *sublayer);
void UILayerRemoveSublayer(UILayer *layer, UILayer *sublayer);
void UILayerAddAnimation(UILayer *layer, UIAnimation anim);

void UILayerRenderInContext(UILayer *layer, UIGraphicsContext *context);
UILayer UILayerGetInFlight(UILayer layer);
