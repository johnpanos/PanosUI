#include <stdlib.h>
#include "UIWindow.h"
#include "UIViewController.h"

UIWindow *UIWindowCreate()
{
    UIWindow *window = malloc(sizeof(UIWindow));
    UIApplicationShared()->window = window;

    _UIPlatformWindowCreate(window);

    return window;
}

void UIWindowDestroy(UIWindow *window)
{
    _UIPlatformWindowDestroy(window);

    UIViewControllerDestroy(window->rootViewController);
    free(window);

    UIApplicationShared()->window = NULL;
}

void UIWindowSetTitle(UIWindow *window, const char *title)
{
    window->title = title;
}

void UIWindowSetRootViewController(UIWindow *window, UIViewController *viewController)
{
    window->rootViewController = viewController;
    viewController->_window = window;
    viewController->loadView(viewController);

    // TODO: Attach a UILayer w/ EGLContext to UIView
}