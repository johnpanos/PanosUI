#include <stdio.h>
#include "PanosUI.h"

void windowDidLoad(UIWindow window)
{
    printf("THE WINDOW LOADED!\n");
}

void windowDidResize(UIWindow window) {
    UIRect newRect = window->frame;
    newRect.height -= 28;
    window->mainView->frame = newRect;
    window->mainView->needsDisplay = 1;
    window->mainView->needsLayout = 1;
}

void didFinishLaunching(UIApplication *application)
{
    UIRect window_frame = {
        .x = 0,
        .y = 0,
        .width = 500,
        .height = 200};
    UIWindow window = UIWindowCreate(window_frame);

    UIWindowController myWindowController = UIWindowControllerCreate();
    myWindowController->windowDidLoad = &windowDidLoad;
    myWindowController->windowDidResize = &windowDidResize;

    window->controller = myWindowController;

    UIWindowShow(window);
    UIWindowSetTitle(window, "C Example");

    UIColor bg = {.r = 246, .g = 246, .b = 246, .a = 255};
    window->mainView->backgroundColor = bg;

    UIRect myRect = UIRectInset(window->mainView->frame, 75, 75, 75, 75);

    UIView testView = UIViewCreate(myRect, myRect);
    // testView->clipToBounds = 1;
    testView->cornerRadius = 255;
    testView->backgroundColor = UIColorCreateRGBA(0, 0, 0, 255);
    UIViewAddSubview(window->mainView, testView);

    UIRect testOffsetRect = {
        .x = 0,
        .y = 0,
        .width = 25,
        .height = 25
    };
    UIView testOffset = UIViewCreate(testOffsetRect, testOffsetRect);
    testOffset->backgroundColor = UIColorCreateRGBA(255, 0, 0, 255);
    UIViewAddSubview(testView, testOffset);
}

static UIApplicationDelegate my_delegate = {
    .didFinishLaunching = &didFinishLaunching};

int main()
{
    UIApplicationMain(&my_delegate);
}