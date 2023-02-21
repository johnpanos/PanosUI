#pragma once

#include "Array.h"
#include "UIGeometry.h"

#include "UIAnimation.h"
#include "UIColor.h"

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

	UILayer *parent;
	Array sublayers;

	UIRect frame; // Calculated, never set

	UIPoint position;
	UIPoint anchorPoint; // x and y are 0.0-1.0 inclusive
	UIRect bounds;

	UIColor backgroundColor;

	UIFloat borderWidth;
	UIColor borderColor;

	UIPoint shadowOffset;
	UIColor shadowColor;
	UIFloat shadowRadius;

	UIFloat opacity;

	UIFloat cornerRadius;
	bool clipToBounds;
} UILayer;

UILayer *UILayerCreate(UIRect frame, UIRect bounds);
void UILayerDestroy(UILayer layer);

// MARK: Setters
void UILayerSetBounds(UILayer *layer, UIRect bounds);
void UILayerSetPosition(UILayer *layer, UIPoint position);
void UILayerSetAnchorPoint(UILayer *layer, UIPoint anchorPoint);

// MARK: Getters
UIRect UILayerGetFrame(UILayer *layer);
UIRect UILayerGetBounds(UILayer *layer);
UIPoint UILayerGetPosition(UILayer *layer);
UIPoint UILayerGetAnchorPoint(UILayer *layer);

// MARK: Animations
void UILayerAddAnimation(UILayer *layer, UIAnimation anim);
UIAnimation UILayerGetAnimationFor(UILayer *layer, const char *key, size_t valueSize, void *startValue, void *endValue);

// MARK: Sublayers
void UILayerAddSublayer(UILayer *layer, UILayer *sublayer);
void UILayerRemoveSublayer(UILayer *layer, UILayer *sublayer);

// MARK: Rendering
void UILayerRenderInContext(UILayer *layer, UIGraphicsContext *context);
UILayer UILayerGetInFlight(UILayer layer);
