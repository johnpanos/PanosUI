#include <stdlib.h>
#include <string.h>
#include "UIView.h"
#include "shared/Array.h"

void _UIViewDoNothing(UIView view){};

UIView UIViewCreate(UIRect frame, UIRect bounds)
{
    UIView view = calloc(1, sizeof(struct _UIView));
    view->layer = UILayerCreate();
    view->frame = frame;
    view->bounds = bounds;
    view->subviews = ArrayCreate(sizeof(UIView));
    view->needsDisplay = 1;
    view->needsLayout = 1;
    view->layoutSubviews = &_UIViewDoNothing;
    return view;
}

void UIViewDestroy(UIView view)
{
    for (int i = 0; i < ArrayGetCapacity(view->subviews); i++)
    {
        UIView child = ArrayGetValueAtIndex(view->subviews, i);
        child->parentView = NULL;
    }
    if (view->subviews != NULL)
    {
        ArrayDestroy(view->subviews);
    }

    free(view);
}

void UIViewAddSubview(UIView superview, UIView subview)
{
    ArrayAddValue(superview->subviews, subview);
    subview->parentView = superview;
}

void UIViewRemoveSubview(UIView superview, UIView subview)
{
    ArrayRemoveValueByRef(superview->subviews, subview);
    subview->parentView = NULL;
}

void UIViewDrawInContext(UIView view, UIGraphicsContext *context)
{
    if (view->clipToBounds)
    {
        UIGraphicsContextClipToRect(context, view->frame, view->cornerRadius);
    }

    if (view->shadowColor.a > 0)
    {
        UIGraphicsContextSave(context);
        {
            UIGraphicsContextSetShadow(context, view->shadowOffset, view->shadowRadius);
            UIGraphicsSetFillColor(context, view->shadowColor);
            UIGraphicsContextAddRect(context, view->frame, view->cornerRadius);
        }
        UIGraphicsContextRestore(context);
    }

    UIGraphicsSetFillColor(context, view->backgroundColor);
    UIGraphicsContextAddRect(context, view->frame, view->cornerRadius);

    if (view->borderWidth > 0)
    {
        UIGraphicsSetStrokeColor(context, view->borderColor);
        UIGraphicsSetStrokeWidth(context, view->borderWidth);
        UIGraphicsContextAddRect(context, view->frame, view->cornerRadius);
    }
}

void UIViewSetNeedsDisplay(UIView view)
{
    UIView current = view;
    do
    {
        current->needsDisplay = 1;
        current = current->parentView;
    } while (current != NULL);
}

UIView UIViewHitTest(UIView view, UIPoint point)
{
    // printf("\nHit test: x(%d) y(%d)\n", point.x, point.y);
    if (!view)
        return NULL;
    if (!UIPointInRect(point, view->frame))
        return NULL;

    for (int i = ArrayGetCapacity(view->subviews) - 1; i >= 0; --i)
    {
        UIView subview = ArrayGetValueAtIndex(view->subviews, i);
        if (!subview->clipToBounds && !UIPointInRect(point, subview->frame))
            continue;
        UIPoint convertedPoint = {
            .x = point.x - subview->frame.x,
            .y = point.y - subview->frame.y};
        // printf("Converted point: x(%d) y(%d)\n", convertedPoint.x, convertedPoint.y);
        UIView hitView = UIViewHitTest(subview, convertedPoint);
        if (hitView)
            return hitView;
    }

    return view;
}