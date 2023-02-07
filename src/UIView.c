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

void UIViewDrawInContext(UIView view, UIGraphicsContext *context) {
    UIGraphicsSetFillColor(context, view->backgroundColor);
    UIGraphicsContextAddRect(context, view->frame, 0);
}

void UIViewSetNeedsDisplay(UIView view) {
    UIView current = view;
    do {
        current->needsDisplay = 1;
        current = current->parentView;
    } while (current != NULL);
}