#ifndef _UIVIEW_H
#define _UIVIEW_H

#include "UIGeometry.h"

#include "UILayer.h"
#include "UIColor.h"
#include "UIEventResponder.h"
#include "Array.h"

typedef struct _UIView *UIView;
typedef struct _UIView
{
    UILayer *layer;
    UIEventResponder responder;

    UIRect frame;
    UIRect bounds;

    UIView parentView;
    Array subviews;

    int needsDisplay;
    int needsLayout;

    void (*layoutSubviews)(UIView view);

    UIColor backgroundColor;
    float cornerRadius;
    UIColor borderColor;
    float borderWidth;

    UIPoint shadowOffset;
    UIColor shadowColor;
    float shadowRadius;

    int clipToBounds;
} *UIView;

UIView UIViewCreate(UIRect frame, UIRect bounds);
void UIViewDestroy(UIView view);

void UIViewAddSubview(UIView superview, UIView subview);
void UIViewRemoveSubview(UIView superview, UIView subview);

UIPoint UIViewConvertPoint(UIView from, UIView to, UIPoint point);
UIView UIViewHitTest(UIView view, UIPoint point);

// MARK: Getters
UIColor UIViewGetBackgroundColor(UIView view);
float UIViewGetCornerRadius(UIView view);
UIColor UIViewGetBorderColor(UIView view);
float UIViewGetBorderWidth(UIView view);

UIPoint UIViewGetShadowOffset(UIView view);
UIColor UIViewGetShadowColor(UIView view);
float UIViewGetShadowRadius(UIView view);

// MARK: Setters
void UIViewSetFrame(UIView view, UIRect frame);
void UIViewSetBounds(UIView view, UIRect bounds);
void UIViewSetBackgroundColor(UIView view, UIColor backgroundColor);
void UIViewSetCornerRadius(UIView view, float cornerRadius);
void UIViewSetBorderColor(UIView view, UIColor borderColor);
void UIViewSetBorderWidth(UIView view, float borderWidth);

void UIViewSetShadowOffset(UIView view, UIPoint shadowOffset);
void UIViewSetShadowColor(UIView view, UIColor shadowColor);
void UIViewSetShadowRadius(UIView view, float shadowRadius);

#endif