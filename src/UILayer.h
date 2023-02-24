#pragma once

#include "UIGeometry.h"
#include "shared/Array.h"

#include "UIAnimation.h"
#include "UIColor.h"
#include "UIGraphicsContext.h"
#include "include/UILayerDelegate.h"

// MARK: Struct Defs
typedef struct _UIPlatformLayer UIPlatformLayer;
typedef struct _UILayerDelegate UILayerDelegate;
typedef struct _UILayer UILayer;
typedef struct _UILayer
{
	Array animations;

	UILayerDelegate delegate;

	UILayer *parent;
	Array sublayers;

	UIRect frame; // Calculated, never set

	UIPoint position;
	UIPoint anchorPoint; // x and y are 0.0-1.0 inclusive
	UIRect bounds;

	UIColor *backgroundColor;

	UIFloat borderWidth;
	UIColor *borderColor;

	UIPoint shadowOffset;
	UIColor *shadowColor;
	UIFloat shadowRadius;

	UIFloat opacity;

	UIFloat cornerRadius;
	bool clipToBounds;

	UIPlatformLayer *platformLayer;
} UILayer;

// MARK: Rendering
void UILayerRenderInContext(const UILayer *layer, UIGraphicsContext *context);
UILayer UILayerGetInFlight(UILayer *layer);
