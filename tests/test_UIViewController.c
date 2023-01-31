#include <assert.h>
#include <stdio.h>

#include "UIViewController.h"
#include "UIView.h"

static int didLoad = 0;

void viewDidLoad(UIViewController *this)
{
    assert(this->view != NULL);
    didLoad = 1;
}

void loadView(UIViewController *this)
{
    UIRect rect;
    rect.x = 0;
    rect.y = 0;
    rect.width = 100;
    rect.height = 100;

    this->view = UIViewCreate(rect, rect);
    this->viewDidLoad(this);
}

int main()
{
    UIViewController *viewController = UIViewControllerCreate();
    viewController->loadView = &loadView;
    viewController->viewDidLoad = &viewDidLoad;

    viewController->loadView(viewController);
    assert(didLoad);

    UIViewControllerDestroy(viewController);

    return 0;
}