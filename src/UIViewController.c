#include <stdlib.h>
#include "UIViewController.h"

void UIViewControllerLoadView(UIViewController *this)
{
    UIView *view = UIViewCreate(this->_window->frame, this->_window->frame);
    this->view = view;
    this->viewDidLoad(this);
}

UIViewController *UIViewControllerCreate()
{
    UIViewController *viewController = malloc(sizeof(UIViewController));
    viewController->loadView = &UIViewControllerLoadView;
    viewController->viewDidLoad = NULL;
    viewController->view = NULL;
    viewController->_window = NULL;
    return viewController;
}

void UIViewControllerDestroy(UIViewController *viewController)
{
    viewController->_window = NULL;
    if (viewController->view != NULL)
    {
        UIViewDestroy(viewController->view);
    }
    free(viewController);
}