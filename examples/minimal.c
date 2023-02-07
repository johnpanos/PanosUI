#include <stdio.h>
#include "PanosUI.h"

void CreateMacOSWindow() {
UIRect window_frame = {
        .x = 0,
        .y = 0,
        .width = 556,
        .height = 198};
    UIWindow window = UIWindowCreate(window_frame);
    UIWindowSetTitle(window, "C Example");

    UIColor bg = {.r = 255, .g = 255, .b = 255, .a = 255};
    window->mainView->backgroundColor = bg;
    window->mainView->cornerRadius = 10.0f;
    window->mainView->borderColor = UIColorCreateRGBA(0, 0, 0, 21);

    UIRect sidebarFrame = {.x = 0, .y = 0, .width = 156, .height = window->mainView->frame.height};
    UIView sidebar = UIViewCreate(sidebarFrame, sidebarFrame);
    sidebar->backgroundColor = UIColorCreateRGBA(218, 218, 218, 255);
    UIViewAddSubview(window->mainView, sidebar);

    UIRect f = {.x = 20, .y = 20, .width = 12, .height = 12};
    UIColor b = {.r = 255, .g = 94, .b = 87, .a = 255};
    UIView myView = UIViewCreate(f, f);
    myView->cornerRadius = 12;
    myView->backgroundColor = b;
    myView->borderColor = UIColorCreateRGBA(0, 0, 0, 21);

    UIRect yellowFrame = {.x = 20 + 20, .y = 20, .width = 12, .height = 12};
    UIColor yellow = {.r = 255, .g = 187, .b = 46, .a = 255};
    UIView yellowLight = UIViewCreate(yellowFrame, yellowFrame);
    yellowLight->cornerRadius = 12;
    yellowLight->backgroundColor = yellow;
    yellowLight->borderColor = UIColorCreateRGBA(0, 0, 0, 21);

    UIRect greenFrame = {.x = 20 + 20 + 20, .y = 20, .width = 12, .height = 12};
    UIColor green = {.r = 56, .g = 193, .b = 73, .a = 255};
    UIView greenLight = UIViewCreate(greenFrame, greenFrame);
    greenLight->cornerRadius = 12;
    greenLight->backgroundColor = green;
    greenLight->borderColor = UIColorCreateRGBA(0, 0, 0, 21);

    UIViewAddSubview(sidebar, myView);
    UIViewAddSubview(sidebar, yellowLight);
    UIViewAddSubview(sidebar, greenLight);
}

void didFinishLaunching(UIApplication *application)
{
    CreateMacOSWindow();
    CreateMacOSWindow();
}

static UIApplicationDelegate my_delegate = {
    .didFinishLaunching = &didFinishLaunching};

int main()
{
    UIApplicationMain(&my_delegate);
}