#pragma once

#include "Array.h"
#include "UIRect.h"
#include "UIColor.h"

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

extern const char *kUILayerKeyOpacity;

typedef struct _UIGraphicsContext UIGraphicsContext;

// MARK: Struct Defs
typedef struct _UILayer
{
    Array animations;
    Array sublayers;

    UIRect frame; // Calculated, never set
    UIRect bounds;

    UIColor backgroundColor;

    float borderWidth;
    UIColor borderColor;

    UIPoint shadowOffset;
    UIColor shadowColor;
    float shadowRadius;

    float opacity;
} UILayer;

UILayer *UILayerCreate(UIRect frame, UIRect bounds);
void UILayerDestroy(UILayer layer);

void UILayerAddSublayer(UILayer *layer, UILayer *sublayer);

void UILayerRenderInContext(UILayer layer, UIGraphicsContext *context);
UILayer UILayerGetInFlight(UILayer layer);
