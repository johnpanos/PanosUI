#include <stdlib.h>
#include <string.h>
#include "UIView.h"

UIView *UIViewCreate(UIRect frame, UIRect bounds)
{
    UIView *view = malloc(sizeof(UIView));
    view->frame = frame;
    view->bounds = bounds;
    view->subviews = NULL;
    view->_subviewCount = 0;
    return view;
}

void UIViewDestroy(UIView *view)
{

    for (int i = 0; i < view->_subviewCount; i++)
    {
        UIView *child = view->subviews[i];
        child->parentView = NULL;
    }
    if (view->subviews != NULL)
    {
        free(view->subviews);
    }

    free(view);
}

void UIViewAddSubview(UIView *superview, UIView *subview)
{
    if (superview->_subviewCount == 0)
    {
        superview->_subviewCount = 1;
        superview->subviews = calloc(superview->_subviewCount, sizeof(UIView *));
        superview->subviews[0] = subview;
    }
    else
    {
        superview->_subviewCount += 1;
        superview->subviews = realloc(superview->subviews, superview->_subviewCount * sizeof(UIView *));
        superview->subviews[superview->_subviewCount - 1] = subview;
    }

    subview->parentView = superview;
}

void UIViewRemoveSubview(UIView *superview, UIView *subview)
{
    UIView ***array = &superview->subviews;
    int *n = &superview->_subviewCount;

    int i = -1;
    for (int j = 0; j < *n; j++)
    {
        if ((*array)[j] == subview)
        {
            i = j;
            break;
        }
    }

    if (i == -1)
    {
        return;
    }

    UIView *removedView = (*array)[i];
    removedView->parentView = NULL;

    memcpy(&(*array)[i], &(*array)[i + 1], (*n - i - 1) * sizeof(UIView *));

    (*array) = realloc(*array, (*n - 1) * sizeof(UIView *));
    (*n)--;
}