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

typedef struct _UILayerDelegate UILayerDelegate;
typedef struct _UILayer UILayer;

UILayer *UILayerCreate(UIRect frame, UIRect bounds);
void UILayerDestroy(UILayer *layer);

// delegate
UILayerDelegate UILayerGetDelegate(const UILayer *layer);
void UILayerSetDelegate(UILayer *layer, UILayerDelegate delegate);

// parent
UILayer *UILayerGetParent(const UILayer *layer);
void UILayerSetParent(UILayer *layer, UILayer *parent);

// frame
UIRect UILayerGetFrame(const UILayer *layer);

// bounds
UIRect UILayerGetBounds(const UILayer *layer);
void UILayerSetBounds(UILayer *layer, UIRect bounds);

// position
UIPoint UILayerGetPosition(const UILayer *layer);
void UILayerSetPosition(UILayer *layer, UIPoint position);

// anchorPoint
UIPoint UILayerGetAnchorPoint(const UILayer *layer);
void UILayerSetAnchorPoint(UILayer *layer, UIPoint anchorPoint);

// backgroundColor
UIColor *UILayerGetBackgroundColor(const UILayer *layer);
void UILayerSetBackgroundColor(UILayer *layer, UIColor *backgroundColor);

// borderWidth
UIFloat UILayerGetBorderWidth(const UILayer *layer);
void UILayerSetBorderWidth(UILayer *layer, UIFloat borderWidth);

// borderColor
UIColor *UILayerGetBorderColor(const UILayer *layer);
void UILayerSetBorderColor(UILayer *layer, UIColor *borderColor);

// shadowOffset
UIPoint UILayerGetShadowOffset(const UILayer *layer);
void UILayerSetShadowOffset(UILayer *layer, UIPoint shadowOffset);

// shadowColor
UIColor *UILayerGetShadowColor(const UILayer *layer);
void UILayerSetShadowColor(UILayer *layer, UIColor *shadowColor);

// shadowRadius
UIFloat UILayerGetShadowRadius(const UILayer *layer);
void UILayerSetShadowRadius(UILayer *layer, UIFloat shadowRadius);

// opacity
UIFloat UILayerGetOpacity(const UILayer *layer);
void UILayerSetOpacity(UILayer *layer, UIFloat opacity);

// cornerRadius
UIFloat UILayerGetCornerRadius(const UILayer *layer);
void UILayerSetCornerRadius(UILayer *layer, UIFloat cornerRadius);

// clipToBounds
bool UILayerGetClipToBounds(const UILayer *layer);
void UILayerSetClipToBounds(UILayer *layer, bool clipToBounds);

// MARK: Animations
void UILayerAddAnimation(UILayer *layer, UIAnimation anim);
UIAnimation UILayerGetAnimationFor(UILayer *layer, const char *key, size_t valueSize, void *startValue, void *endValue);

// MARK: Sublayers
void UILayerAddSublayer(UILayer *layer, UILayer *sublayer);
void UILayerRemoveSublayer(UILayer *layer, UILayer *sublayer);