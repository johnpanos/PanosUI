#ifndef _UIVIEWCONTROLLER_H
#define _UIVIEWCONTROLLER_H

#include "UIView.h"

typedef struct _UIViewController UIViewController;
typedef struct _UIViewController
{
    UIView *view;

    void (*loadView)(UIViewController *self);
    void (*viewDidLoad)(UIViewController *self);
} UIViewController;

UIViewController *UIViewControllerCreate();
void UIViewControllerDestroy(UIViewController *viewController);

#endif