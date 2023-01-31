#ifndef _UIVIEW_H
#define _UIVIEW_H

#include "UIRect.h"
#include "UILayer.h"

typedef struct _UIView UIView;
typedef struct _UIView
{
    UILayer *layer;
    UIRect frame;
    UIRect bounds;

    UIView *parentView;

    UIView **subviews;
    int _subviewCount;
} UIView;

UIView *UIViewCreate(UIRect frame, UIRect bounds);
void UIViewDestroy(UIView *view);

void UIViewAddSubview(UIView *superview, UIView *subview);
void UIViewRemoveSubview(UIView *superview, UIView *subview);

#endif