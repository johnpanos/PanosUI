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

UIView createSwitchView() {
    UIRect frame = {
        .x = 0,
        .y = 0,
        .width = 40,
        .height = 22
    };
    UIView switchView = UIViewCreate(frame, frame);
    switchView->clipToBounds = 1;
    switchView->cornerRadius = 100.0f;
    switchView->backgroundColor = UIColorCreateRGBA(0, 122, 255, 255);
    switchView->borderWidth = 1.5f;
    switchView->borderColor = UIColorCreateRGBA(0, 0, 0, 31);

    UIRect knobFrame ={
        .x = 19,
        .y = 1,
        .width = 20,
        .height = 20
    };
    UIView knobView = UIViewCreate(knobFrame, knobFrame);
    knobView->clipToBounds = 1;
    knobView->cornerRadius = 20.0f;
    knobView->backgroundColor = UIColorCreateRGBA(255, 255, 255, 255);
    knobView->borderWidth = 0.0f;
    knobView->borderColor = UIColorCreateRGBA(0, 0, 0, 31);

    UIViewAddSubview(switchView, knobView);

    return switchView;
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

    UIViewAddSubview(window->mainView, createSwitchView());
}

static UIApplicationDelegate my_delegate = {
    .didFinishLaunching = &didFinishLaunching};

int main()
{
    UIApplicationMain(&my_delegate);
}