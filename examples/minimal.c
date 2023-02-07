#include <stdio.h>
#include "PanosUI.h"

void didFinishLaunching(UIApplication *application)
{
    UIRect window_frame = {
        .x = 0,
        .y = 0,
        .width = 300,
        .height = 300};
    UIWindow window = UIWindowCreate(window_frame);
    UIWindowSetTitle(window, "C Example");

    UIColor bg = {.r = 255, .g = 0, .b = 0, .a = 255};
    UIRect f = {.x = 10, .y = 10, .width = 20, .height = 20};
    window->mainView->backgroundColor = bg;

    UIColor b = {.r = 0, .g = 0, .b = 0, .a = 255};
    UIView myView = UIViewCreate(f, f);
    myView->backgroundColor = b;
    UIViewAddSubview(window->mainView, myView);
}

static UIApplicationDelegate my_delegate = {
    .didFinishLaunching = &didFinishLaunching};

int main()
{
    UIApplicationMain(&my_delegate);
}