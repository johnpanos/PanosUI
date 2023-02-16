#include <stdio.h>
#include "PanosUI.h"

void windowDidLoad(UIWindow window)
{
    UIView view = window->mainView;

    UIRect frameRect = UIRectCreate(0, 0, 200, 200);
    UIView view2 = UIViewCreate(frameRect, frameRect);

    UIViewSetBackgroundColor(view2, UIColorCreateRGBA(0, 0, 0, 255));
    UILayerSetAnchorPoint(view2->layer, UIPointCreate(0.25f, 0.25f));
    UIViewSetFrame(view2, UIRectCreate(10, 10, 750 - 20, 600 - 20));

    UIViewAddSubview(view, view2);

    UIFloat start = view2->frame.size.width;
    UIFloat end = 50.0f;
    UIAnimation radiusAnim;
    radiusAnim.finished = 0;
    radiusAnim.forKey = kUILayerKeyBoundsWidth;
    radiusAnim.timingFunction = &UIAnimationTimingFunctionEaseInOutBounce;
    radiusAnim.startValue = &start;
    radiusAnim.endValue = &end;
    radiusAnim.startTime = UIAnimationGetCurrentTime();
    radiusAnim.endTime = UIAnimationGetCurrentTime() + 3000;
    radiusAnim._valueSize = sizeof(UIFloat);
    radiusAnim.duration = 3000;

    UILayerAddAnimation(view2->layer, radiusAnim);

    radiusAnim.forKey = kUILayerKeyBoundsHeight;
    start = view2->frame.size.height;
    end = 50.0f;
    UILayerAddAnimation(view2->layer, radiusAnim);

    radiusAnim.forKey = kUILayerKeyCornerRadius;
    start = 0.0f;
    end = 64.0f;
    UILayerAddAnimation(view2->layer, radiusAnim);

    UIRect view3Frame = UIRectCreate(10, 10, 300, 300);
    UIView view3 = UIViewCreate(view3Frame, view3Frame);
    UIViewSetBackgroundColor(view3, UIColorCreateRGBA(0, 0, 255, 255));

    // UIViewAddSubview(window->mainView, view3);
}

void didFinishLaunching(UIApplication *application)
{
    UIRect windowFrame = UIRectCreate(0, 0, 750, 600);
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