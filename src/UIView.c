#include <stdlib.h>
#include <string.h>
#include "UIView.h"
#include "shared/Array.h"

UIView UIViewCreate(UIRect frame, UIRect bounds)
{
    UIView view = malloc(sizeof(struct _UIView));
    view->frame = frame;
    view->bounds = bounds;
    view->parentView = NULL;
    view->subviews = ArrayCreate(sizeof(UIView));
    view->needsDisplay = 1;
    view->cornerRadius = 0.0f;
    view->backgroundColor = UIColorCreateRGBA(0, 0, 0, 0);
    view->borderColor = UIColorCreateRGBA(0, 0, 0, 0);
    view->borderWidth = 0.0f;
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
    {
        if (view->clipToBounds)
        {
            UIGraphicsContextClipToRect(context, view->frame, view->cornerRadius);
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