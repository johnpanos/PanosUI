#pragma once

#include "UIAnimation.h"
#include "UIColor.h"
#include "UIGeometry.h"

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

typedef struct _UILayer UILayer;

UILayer *UILayerCreate(UIRect frame, UIRect bounds);
void UILayerDestroy(UILayer *layer);

// MARK: Setters
void UILayerSetBounds(UILayer *layer, UIRect bounds);
void UILayerSetPosition(UILayer *layer, UIPoint position);
void UILayerSetAnchorPoint(UILayer *layer, UIPoint anchorPoint);

// MARK: Getters
UIRect UILayerGetFrame(const UILayer *layer);
UIRect UILayerGetBounds(const UILayer *layer);
UIPoint UILayerGetPosition(const UILayer *layer);
UIPoint UILayerGetAnchorPoint(const UILayer *layer);

// MARK: Animations
void UILayerAddAnimation(UILayer *layer, UIAnimation anim);
UIAnimation UILayerGetAnimationFor(UILayer *layer, const char *key, size_t valueSize, void *startValue, void *endValue);

// MARK: Sublayers
void UILayerAddSublayer(UILayer *layer, UILayer *sublayer);
void UILayerRemoveSublayer(UILayer *layer, UILayer *sublayer);