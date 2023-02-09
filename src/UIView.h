#pragma once

#include "UIRect.h"
#include "UIColor.h"
#include "UILayer.h"
#include "shared/Array.h"

typedef struct _UIView *UIView;
typedef struct _UIView
{
    UILayer *layer;
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

void UIViewDrawInContext(UIView view, UIGraphicsContext *context);

void UIViewSetNeedsLayout(UIView view);
void UIViewSetNeedsDisplay(UIView view);

UIView UIViewHitTest(UIView view, UIPoint point);