#ifndef _UIVIEWCONTROLLER_H
#define _UIVIEWCONTROLLER_H

#include "UIView.h"
#include "UIWindow.h"

struct _UIViewController
{
    UIView *view;

    void (*loadView)(struct _UIViewController *this);
    void (*viewDidLoad)(struct _UIViewController *this);

    UIWindow *_window;
};

struct _UIViewController *UIViewControllerCreate();
void UIViewControllerDestroy(struct _UIViewController *viewController);

#endif