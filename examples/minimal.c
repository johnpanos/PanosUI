#include <stdio.h>
#include "UIApplication.h"
#include "UIWindow.h"
#include "UIViewController.h"
#include "UIView.h"

void viewDidLoad(UIViewController *this)
{
    UIRect rect;
    rect.x = 0;
    rect.y = 0;
    rect.width = 100;
    rect.height = 100;

    UIView *my_view = UIViewCreate(rect, rect);
    UIViewAddSubview(this->view, my_view);

    printf("uiview width: %d\n", this->view->subviews[0]->frame.width);
}

void didFinishLaunching(UIApplication *application)
{
    UIWindow *window = UIWindowCreate();
    UIWindowSetTitle(window, "My Window");

    UIViewController *rootViewController = UIViewControllerCreate();
    rootViewController->viewDidLoad = &viewDidLoad;

    UIWindowSetRootViewController(window, rootViewController);
}

static UIApplicationDelegate my_delegate = {
    .didFinishLaunching = &didFinishLaunching};

int main()
{
    UIApplicationMain(&my_delegate);
}