#pragma once

#include "Array.h"
#include "UIRect.h"
#include "UIPoint.h"
#include "UIColor.h"
#include "UIAnimation.h"

typedef struct _UIGraphicsContext UIGraphicsContext;

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
typedef struct _UIGraphicsContext UIGraphicsContext;
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
} UILayer;

UILayer *UILayerCreate(UIRect frame, UIRect bounds);
void UILayerDestroy(UILayer layer);

void UILayerAddSublayer(UILayer *layer, UILayer *sublayer);
void UILayerAddAnimation(UILayer *layer, UIAnimation anim);

void UILayerRenderInContext(UILayer *layer, UIGraphicsContext *context);
UILayer UILayerGetInFlight(UILayer layer);
