#include "UIView.h"
#include "include/UIGeometry.h"
#include "include/UIView.h"
#include "shared/Array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _UIViewDoNothing(UIView *view)
{
	view->needsLayout = 0;
};

UIView *UIViewCreate(UIRect frame, UIRect bounds)
{
	UIView *view = calloc(1, sizeof(struct _UIView));
	view->parentView = NULL;
	view->layer = UILayerCreate(frame, frame);
	view->backgroundColor = UIColorCreateRGBA(255, 255, 255, 255);
	view->borderColor = UIColorCreateRGBA(255, 255, 255, 0);
	view->shadowColor = UIColorCreateRGBA(255, 255, 255, 0);

	view->responder = UIEventResponderCreate();
	UIViewSetFrame(view, frame);
	UIRect boundsCopy = bounds;
	boundsCopy.origin.x = 0;
	boundsCopy.origin.y = 0;
	UIViewSetBounds(view, boundsCopy);
	view->subviews = ArrayCreate(sizeof(UIView *));
	view->needsDisplay = 1;
	view->needsLayout = 1;
	view->layoutSubviews = &_UIViewDoNothing;

	return view;
}

void UIViewDestroy(UIView *view)
{
	for (int i = 0; i < ArrayGetCapacity(view->subviews); i++)
	{
		UIView *child = ArrayGetValueAtIndex(view->subviews, i);
		child->parentView = NULL;
	}
	if (view->subviews != NULL)
	{
		ArrayDestroy(view->subviews);
	}

	free(view);
}

void UIViewAddSubview(UIView *superview, UIView *subview)
{
	ArrayAddValue(superview->subviews, subview);
	subview->parentView = superview;
	UILayerAddSublayer(superview->layer, subview->layer);
}

void UIViewRemoveSubview(UIView *superview, UIView *subview)
{
	ArrayRemoveValueByRef(superview->subviews, subview);
	subview->parentView = NULL;
	UILayerRemoveSublayer(superview->layer, subview->layer);
}

void UIViewSetNeedsDisplay(UIView *view)
{
	UIView *current = view;
	do
	{
		current->needsDisplay = 1;
		current = current->parentView;
	} while (current != NULL);
}

// UIPoint _UIViewConvertPoint(UIView *from, UIView *to,)

UIPoint UIViewConvertPoint(UIView *from, UIView *to, UIPoint point)
{
	// TODO: Add same window check
	UIPoint p = point;
	UIView *parent = UIViewGetParentView(to);

	if (parent == NULL)
	{
		return UIPointCreate(0, 0);
	}

	UIPoint toOffset = to->frame.origin;

	p.x -= toOffset.x;
	p.y -= toOffset.y;

	// p.x += UIRectGetMinX(parent->frame) - UIRectGetMinX(to->frame);
	// p.y += UIRectGetMinY(parent->frame) - UIRectGetMinY(to->frame);

	if (from == parent)
	{
		p.x += parent->frame.origin.x;
		p.y += parent->frame.origin.y;
		return p;
	}
	else if (parent != from)
	{
		// UIPoint delta = UIViewConvertPoint(from, parent, p);
		// p.x += delta.x;
		// p.y += delta.y;
		return UIViewConvertPoint(from, parent, p);
	}

	return UIPointCreate(0, 0);
}

UIView *UIViewHitTest(UIView *view, UIPoint point)
{
	printf("\nHit test: x(%f) y(%f)\n", point.x, point.y);
	if (!view)
		return NULL;
	if (!UIPointInRect(point, view->bounds))
		return NULL;

	for (int i = ArrayGetCapacity(view->subviews) - 1; i >= 0; --i)
	{
		UIView *subview = ArrayGetValueAtIndex(view->subviews, i);
		UIPoint convertedPoint = UIViewConvertPoint(view, subview, point);
		printf("Converted point: x(%f) y(%f)\n", convertedPoint.x, convertedPoint.y);
		UIView *hitView = UIViewHitTest(subview, convertedPoint);
		printf("hitView: %p\n", hitView);
		if (hitView != NULL)
			return hitView;
	}

	return view;
}

// layer
UILayer *UIViewGetLayer(UIView *view)
{
	return view->layer;
}
void UIViewSetLayer(UIView *view, UILayer *layer)
{
	view->layer = layer;
}

// MARK: Getters
UIRect UIViewGetFrame(UIView *view)
{
	return view->frame;
}
UIRect UIViewGetBounds(UIView *view)
{
	return view->bounds;
}

UIView *UIViewGetParentView(UIView *view)
{
	return view->parentView;
}

void UIViewSetParentView(UIView *view, UIView *parent)
{
	view->parentView = parent;
}

UIColor *UIViewGetBackgroundColor(UIView *view)
{
	return view->backgroundColor;
}
UIFloat UIViewGetCornerRadius(UIView *view)
{
	return view->cornerRadius;
}
UIColor *UIViewGetBorderColor(UIView *view)
{
	return view->borderColor;
}
UIFloat UIViewGetBorderWidth(UIView *view)
{
	return view->borderWidth;
}

UIPoint UIViewGetShadowOffset(UIView *view)
{
	return view->shadowOffset;
}
UIColor *UIViewGetShadowColor(UIView *view)
{
	return view->shadowColor;
}
UIFloat UIViewGetShadowRadius(UIView *view)
{
	return view->shadowRadius;
}

// MARK: Setters
void UIViewSetFrame(UIView *view, UIRect frame)
{
	view->frame = frame;

	UIRect layerFrame = frame;
	UIRect layerBounds = view->layer->bounds;

	layerFrame.origin = UIPointOffset(frame.origin, (frame.size.width * view->layer->anchorPoint.x),
									  (frame.size.height * view->layer->anchorPoint.y));

	layerBounds.size = frame.size;

	UILayerSetBounds(view->layer, layerBounds);
	UILayerSetPosition(view->layer, layerFrame.origin);
}
void UIViewSetBounds(UIView *view, UIRect bounds)
{
	view->bounds = bounds;
	UILayerSetBounds(view->layer, bounds);
}
void UIViewSetBackgroundColor(UIView *view, UIColor *backgroundColor)
{
	view->backgroundColor = backgroundColor;
	view->layer->backgroundColor = backgroundColor;
}
void UIViewSetCornerRadius(UIView *view, UIFloat cornerRadius)
{
	view->cornerRadius = cornerRadius;

	UIAnimation anim = UILayerGetAnimationFor(view->layer, kUILayerKeyCornerRadius, sizeof(UIFloat),
											  &view->layer->cornerRadius, &view->cornerRadius);
	UILayerAddAnimation(view->layer, anim);

	view->layer->cornerRadius = cornerRadius;
}
void UIViewSetBorderColor(UIView *view, UIColor *borderColor)
{
	view->borderColor = borderColor;
	view->layer->borderColor = borderColor;
}
void UIViewSetBorderWidth(UIView *view, UIFloat borderWidth)
{
	view->borderWidth = borderWidth;
	view->layer->borderWidth = borderWidth;
}

void UIViewSetShadowOffset(UIView *view, UIPoint shadowOffset)
{
	view->shadowOffset = shadowOffset;
	view->layer->shadowOffset = shadowOffset;
}
void UIViewSetShadowColor(UIView *view, UIColor *shadowColor)
{
	view->shadowColor = shadowColor;
	view->layer->shadowColor = shadowColor;
}
void UIViewSetShadowRadius(UIView *view, UIFloat shadowRadius)
{
	view->shadowRadius = shadowRadius;
	view->layer->shadowRadius = shadowRadius;
}