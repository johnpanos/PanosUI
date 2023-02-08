#ifndef _UIVIEW_H
#define _UIVIEW_H

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

    UIColor backgroundColor;
    UIColor borderColor;
    float borderWidth;

    float cornerRadius;

    int clipToBounds;
} *UIView;

UIView UIViewCreate(UIRect frame, UIRect bounds);
void UIViewDestroy(UIView view);

void UIViewAddSubview(UIView superview, UIView subview);
void UIViewRemoveSubview(UIView superview, UIView subview);

void UIViewDrawInContext(UIView view, UIGraphicsContext *context);
void UIViewSetNeedsDisplay(UIView view);

UIView UIViewHitTest(UIView view, UIPoint point);

#endif