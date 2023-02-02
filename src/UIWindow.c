#include <stdlib.h>
#include "UIWindow.h"
#include "UIViewController.h"

UIWindow *UIWindowCreate(UIRect frame)
{
    UIWindow *window = malloc(sizeof(UIWindow));
    UIApplicationShared()->window = window;
    window->frame = frame;

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
    _UIPlatformWindowSetTitle(window, title);
}

void UIWindowSetRootViewController(UIWindow *window, UIViewController *viewController)
{
    window->rootViewController = viewController;
    viewController->_window = window;
    viewController->loadView(viewController);

    // TODO: Attach a UILayer w/ EGLContext to UIView
}