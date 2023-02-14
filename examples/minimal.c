#include <stdio.h>
#include "PanosUI.h"

UIView VIEW;

void onViewClick(UIEventResponder self, UIEvent event)
{
    printf("On Click\n");
    int end = 200;

    UIAnimation radiusAnim;
    radiusAnim.finished = 0;
    radiusAnim.forKey = kUILayerKeyBoundsWidth;
    radiusAnim.timingFunction = &UIAnimationTimingFunctionEaseOutBounce;
    radiusAnim.startValue = &VIEW->frame.size.width;
    radiusAnim.endValue = &end;
    radiusAnim.startTime = UIAnimationGetCurrentTime();
    radiusAnim.endTime = UIAnimationGetCurrentTime() + 5000;
    radiusAnim._valueSize = sizeof(int);
    radiusAnim.duration = 5000;

    UILayerAddAnimation(VIEW->layer, radiusAnim);
}

void windowDidLoad(UIWindow window)
{
    printf("THE WINDOW LOADED!\n");

    // UIRect rect1 = UIRectCreate(50, 50, 128, 128);
    // UIView view1 = UIViewCreate(rect1, rect1);

    // UIRect rect2 = UIRectCreate(200, 200, 128, 128);
    // UIView view2 = UIViewCreate(rect2, rect2);

    // UIPoint tap = UIPointCreate(10, 10);
    // UIPoint convertedTap = UIViewConvertPoint(view1, view2, tap);

    // printf("Converted tap: x(%f) y(%f)\n", convertedTap.x, convertedTap.y);

    UIRect myRect = UIRectCreate(100, 100, 100, 100);
    UIView testView = UIViewCreate(myRect, myRect);
    VIEW = testView;

    // testView->responder->leftMouseDown = &onViewClick;

    UIViewSetBackgroundColor(testView, UIColorCreateRGBA(200, 200, 200, 255));
    UIViewSetCornerRadius(testView, 10.0f);
    UIViewSetShadowColor(testView, UIColorCreateRGBA(0, 0, 0, 100));
    UIPoint shadowOffset = {
        .x = 10,
        .y = 10};
    UIViewSetShadowOffset(testView, shadowOffset);
    UIViewSetShadowRadius(testView, 10.0f);
    UIViewAddSubview(window->mainView, testView);

    UIRect newRect = UIRectInset(window->frame, 36.0f, 36.0f);

    UIFloat start, end;

    start = testView->frame.origin.x;
    end = 36.0f/2.0f;

    UIAnimation radiusAnim;
    radiusAnim.finished = 0;
    radiusAnim.forKey = kUILayerKeyPositionX;
    radiusAnim.timingFunction = &UIAnimationTimingFunctionEaseOutBounce;
    radiusAnim.startValue = &start;
    radiusAnim.endValue = &end;
    radiusAnim.startTime = UIAnimationGetCurrentTime();
    radiusAnim.endTime = UIAnimationGetCurrentTime() + 2500;
    radiusAnim._valueSize = sizeof(UIFloat);
    radiusAnim.duration = 2500;
    UILayerAddAnimation(VIEW->layer, radiusAnim);

    start = testView->frame.origin.y;
    end = 36.0f/2.0f;

    radiusAnim.forKey = kUILayerKeyPositionY;
    UILayerAddAnimation(VIEW->layer, radiusAnim);

    start = testView->frame.size.width;
    end = newRect.size.width;
    radiusAnim.forKey = kUILayerKeyBoundsWidth;
    UILayerAddAnimation(VIEW->layer, radiusAnim);

    start = testView->frame.size.height;
    end = newRect.size.height;
    radiusAnim.forKey = kUILayerKeyBoundsHeight;
    UILayerAddAnimation(VIEW->layer, radiusAnim);

    start = 0.0f;
    end = 10.0f;
    radiusAnim.forKey = kUILayerKeyCornerRadius;
    UILayerAddAnimation(VIEW->layer, radiusAnim);

    start = 48.0f;
    end = 8.0f;
    radiusAnim.forKey = kUILayerKeyShadowRadius;
    UILayerAddAnimation(VIEW->layer, radiusAnim);
}

void didFinishLaunching(UIApplication *application)
{
    UIRect windowFrame = UIRectCreate(0, 0, 500, 600);
    UIWindow window = UIWindowCreate(windowFrame);

    UIWindowController myWindowController = UIWindowControllerCreate();
    myWindowController->windowDidLoad = &windowDidLoad;

    window->controller = myWindowController;

    UIWindowShow(window);
    UIWindowSetTitle(window, "C Example");
}

static UIApplicationDelegate my_delegate = {
    .didFinishLaunching = &didFinishLaunching};

int main()
{
    UIApplicationMain(&my_delegate);
}