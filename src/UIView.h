#pragma once

#include "include/UIView.h"

#include "UIGeometry.h"

#include "UIColor.h"
#include "UIEventResponder.h"
#include "UILayer.h"
#include "shared/Array.h"

struct _UIView
{
	UILayer *layer;
	UIEventResponder *responder;

	UIRect frame;
	UIRect bounds;

	struct _UIView *parentView;
	Array subviews;

	bool needsDisplay;
	bool needsLayout;
	bool clipToBounds;

	void (*layoutSubviews)(UIView *view);

	UIColor *backgroundColor;
	UIFloat cornerRadius;
	UIColor *borderColor;
	UIFloat borderWidth;

	UIPoint shadowOffset;
	UIColor *shadowColor;
	UIFloat shadowRadius;
};