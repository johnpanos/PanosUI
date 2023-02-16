#include <stdlib.h>
#include <string.h>
#include "UIView.h"
#include "shared/Array.h"

void _UIViewDoNothing(UIView view)
{
    view->needsLayout = 0;
};

UIView UIViewCreate(UIRect frame, UIRect bounds)
{
    UIView view = calloc(1, sizeof(struct _UIView));
    view->layer = UILayerCreate(frame, frame);

    view->responder = UIEventResponderCreate();
    UIViewSetFrame(view, frame);
    UIRect boundsCopy = bounds;
    boundsCopy.origin.x = 0;
    boundsCopy.origin.y = 0;
    UIViewSetBounds(view, boundsCopy);
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
    UILayerAddSublayer(superview->layer, subview->layer);
}

void UIViewRemoveSubview(UIView superview, UIView subview)
{
    ArrayRemoveValueByRef(superview->subviews, subview);
    subview->parentView = NULL;
    UILayerRemoveSublayer(superview->layer, subview->layer);
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

UIPoint UIViewConvertPoint(UIView from, UIView to, UIPoint point)
{
    UIPoint p = point;

    p.x += UIRectGetMinX(from->frame) - UIRectGetMinX(to->frame);
    p.y += UIRectGetMinY(from->frame) - UIRectGetMinY(to->frame);

    return p;
}

UIView UIViewHitTest(UIView view, UIPoint point)
{
    printf("\nHit test: x(%f) y(%f)\n", point.x, point.y);
    if (!view)
        return NULL;
    if (!UIPointInRect(point, view->bounds))
        return NULL;

    for (int i = ArrayGetCapacity(view->subviews) - 1; i >= 0; --i)
    {
        UIView subview = ArrayGetValueAtIndex(view->subviews, i);
        UIPoint convertedPoint = UIViewConvertPoint(view, subview, point);
        printf("Converted point: x(%f) y(%f)\n", convertedPoint.x, convertedPoint.y);
        UIView hitView = UIViewHitTest(subview, convertedPoint);
        printf("hitView: %p\n", hitView);
        if (hitView != NULL)
            return hitView;
    }

    return view;
}

// MARK: Getters
UIColor UIViewGetBackgroundColor(UIView view)
{
    return view->backgroundColor;
};
float UIViewGetCornerRadius(UIView view)
{
    return view->cornerRadius;
};
UIColor UIViewGetBorderColor(UIView view)
{
    return view->borderColor;
};
float UIViewGetBorderWidth(UIView view)
{
    return view->borderWidth;
};

UIPoint UIViewGetShadowOffset(UIView view)
{
    return view->shadowOffset;
};
UIColor UIViewGetShadowColor(UIView view)
{
    return view->shadowColor;
};
float UIViewGetShadowRadius(UIView view)
{
    return view->shadowRadius;
};

// MARK: Setters
void UIViewSetFrame(UIView view, UIRect frame)
{
    view->frame = frame;

    UIRect layerFrame = frame;
    UIRect layerBounds = view->layer->bounds;

    layerFrame.origin = UIPointOffset(
        frame.origin,
        (frame.size.width * view->layer->anchorPoint.x),
        (frame.size.height * view->layer->anchorPoint.y));

    layerBounds.size = frame.size;

    UILayerSetBounds(view->layer, layerBounds);
    UILayerSetPosition(view->layer, layerFrame.origin);
}
void UIViewSetBounds(UIView view, UIRect bounds)
{
    view->bounds = bounds;
    UILayerSetBounds(view->layer, bounds);
}
void UIViewSetBackgroundColor(UIView view, UIColor backgroundColor)
{
    view->backgroundColor = backgroundColor;
    view->layer->backgroundColor = backgroundColor;
}
void UIViewSetCornerRadius(UIView view, float cornerRadius)
{
    view->cornerRadius = cornerRadius;

    UIAnimation anim = UILayerGetAnimationFor(
        view->layer,
        kUILayerKeyCornerRadius,
        sizeof(float),
        &view->layer->cornerRadius,
        &view->cornerRadius);
    UILayerAddAnimation(view->layer, anim);

    view->layer->cornerRadius = cornerRadius;
}
void UIViewSetBorderColor(UIView view, UIColor borderColor)
{
    view->borderColor = borderColor;
    view->layer->borderColor = borderColor;
}
void UIViewSetBorderWidth(UIView view, float borderWidth)
{
    view->borderWidth = borderWidth;
    view->layer->borderWidth = borderWidth;
}

void UIViewSetShadowOffset(UIView view, UIPoint shadowOffset)
{
    view->shadowOffset = shadowOffset;
    view->layer->shadowOffset = shadowOffset;
}
void UIViewSetShadowColor(UIView view, UIColor shadowColor)
{
    view->shadowColor = shadowColor;
    view->layer->shadowColor = shadowColor;
}
void UIViewSetShadowRadius(UIView view, float shadowRadius)
{
    view->shadowRadius = shadowRadius;
    view->layer->shadowRadius = shadowRadius;
}