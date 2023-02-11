#include <stdio.h>
#include "PanosUI.h"

void windowDidLoad(UIWindow window)
{
    printf("THE WINDOW LOADED!\n");
}

UIView VIEW;

void onViewClick(UIEventResponder self, UIEvent event)
{
    printf("On Click\n");
    int end = 200;

    UIAnimation radiusAnim;
    radiusAnim.finished = 0;
    radiusAnim.forKey = kUILayerKeyBoundsWidth;
    radiusAnim.timingFunction = &UIAnimationTimingFunctionEaseOutBounce;
    radiusAnim.startValue = &VIEW->frame.width;
    radiusAnim.endValue = &end;
    radiusAnim.startTime = UIAnimationGetCurrentTime();
    radiusAnim.endTime = UIAnimationGetCurrentTime() + 5000;
    radiusAnim._valueSize = sizeof(int);
    radiusAnim.duration = 5000;

    UILayerAddAnimation(VIEW->layer, radiusAnim);
}

void didFinishLaunching(UIApplication *application)
{
    UIRect window_frame = {
        .x = 0,
        .y = 0,
        .width = 600,
        .height = 600};
    UIWindow window = UIWindowCreate(window_frame);

    UIWindowController myWindowController = UIWindowControllerCreate();
    myWindowController->windowDidLoad = &windowDidLoad;

    window->controller = myWindowController;

    UIWindowShow(window);
    UIWindowSetTitle(window, "C Example");

    UIColor bg = {.r = 246, .g = 246, .b = 246, .a = 255};
    window->mainView->backgroundColor = bg;

    UIRect myRect = window->mainView->frame;
    myRect.height = 100;
    myRect.width = 100;

    UIView testView = UIViewCreate(myRect, myRect);
    VIEW = testView;

    testView->responder->leftMouseDown = &onViewClick;

    UIViewSetBackgroundColor(testView, UIColorCreateRGBA(200, 200, 200, 255));
    UIViewSetCornerRadius(testView, 10.0f);
    UIViewSetShadowColor(testView, UIColorCreateRGBA(0, 0, 0, 100));
    UIPoint shadowOffset = {
        .x = 10,
        .y = 10};
    UIViewSetShadowOffset(testView, shadowOffset);
    UIViewSetShadowRadius(testView, 10.0f);
    UIViewAddSubview(window->mainView, testView);

    // radiusAnim.forKey = kUILayerKeyBoundsHeight;
    // radiusAnim.startValue = &testView->frame.y;
    // radiusAnim.endValue = &end;
    // radiusAnim.startTime = UIAnimationGetCurrentTime();
    // radiusAnim.endTime = UIAnimationGetCurrentTime() + 5000;
    // UILayerAddAnimation(testView->layer, radiusAnim);
}

static UIApplicationDelegate my_delegate = {
    .didFinishLaunching = &didFinishLaunching};

int main()
{
    UIApplicationMain(&my_delegate);
}