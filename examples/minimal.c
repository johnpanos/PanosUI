#include <stdio.h>
#include "PanosUI.h"

void windowDidLoad(UIWindow window)
{
    printf("THE WINDOW LOADED!\n");
}

UIView insetView = NULL;

void windowDidResize(UIWindow window)
{
    UIRect newRect = window->frame;
    newRect.height -= 28;
    window->mainView->frame = newRect;
    window->mainView->needsDisplay = 1;
    window->mainView->needsLayout = 1;
}

void mainViewLayoutSubviews(UIView mainView)
{
    insetView->frame = UIRectInset(mainView->frame, 25, 25, 25, 25);
    insetView->needsDisplay = 1;
    insetView->needsLayout = 1;
}

float startRadius = 0.0f;
float endRadius = 80.0f;
UIAnimation radiusAnim;

void didFinishLaunching(UIApplication *application)
{
    UIRect window_frame = {
        .x = 0,
        .y = 0,
        .width = 500,
        .height = 500};
    UIWindow window = UIWindowCreate(window_frame);

    UIWindowController myWindowController = UIWindowControllerCreate();
    myWindowController->windowDidLoad = &windowDidLoad;
    myWindowController->windowDidResize = &windowDidResize;

    window->controller = myWindowController;

    UIWindowShow(window);
    UIWindowSetTitle(window, "C Example");

    UIColor bg = {.r = 246, .g = 246, .b = 246, .a = 255};
    window->mainView->backgroundColor = bg;

    UIRect myRect = UIRectInset(window->mainView->frame, 50, 50, 50, 50);

    UIView testView = UIViewCreate(myRect, myRect);
    UIViewSetBackgroundColor(testView, UIColorCreateRGBA(255, 255, 255, 255));
    UIViewSetCornerRadius(testView, 10.0f);
    UIViewSetShadowColor(testView, UIColorCreateRGBA(0, 0, 0, 100));
    UIPoint shadowOffset = {
        .x = 10,
        .y = 10};
    UIViewSetShadowOffset(testView, shadowOffset);
    UIViewSetShadowRadius(testView, 0.0f);
    insetView = testView;

    UIViewAddSubview(window->mainView, testView);

    window->mainView->layoutSubviews = &mainViewLayoutSubviews;

    radiusAnim.forKey = kUILayerKeyShadowRadius;
    radiusAnim.startValue = &startRadius;
    radiusAnim.endValue = &endRadius;
    radiusAnim.startTime = UIAnimationGetCurrentTime();
    radiusAnim.endTime = UIAnimationGetCurrentTime() + 5000;
    radiusAnim.duration = 5000;

    ArrayAddValue(insetView->layer->animations, &radiusAnim);
}

static UIApplicationDelegate my_delegate = {
    .didFinishLaunching = &didFinishLaunching};

int main()
{
    UIApplicationMain(&my_delegate);
}