#include <stdio.h>
#include "PanosUI.h"

UIView WindowActionButtonCreate(UIFloat x, UIColor bg)
{
    UIRect f = UIRectCreate(x, 0, 14, 14);
    UIView button = UIViewCreate(f, f);

    UIViewSetCornerRadius(button, 5.0f);
    UIViewSetBackgroundColor(button, bg);

    return button;
}

UIView WindowActionsViewCreate()
{
    UIRect rootFrame = UIRectCreate(16.0f, 16.0f, 58, 14);
    UIView root = UIViewCreate(rootFrame, rootFrame);

    UIViewAddSubview(root, WindowActionButtonCreate(0.0f, UIColorCreateRGBA(107, 122, 255, 255)));
    UIViewAddSubview(root, WindowActionButtonCreate(22.0f, UIColorCreateRGBA(149, 160, 178, 204)));
    UIViewAddSubview(root, WindowActionButtonCreate(44.0f, UIColorCreateRGBA(149, 160, 178, 204)));

    return root;
}

UIView VIEW;

void onViewClick(UIEventResponder self, UIEvent event)
{
    printf("On Click\n");
    UIRect newRect = VIEW->parentView->frame;

    UIFloat start, end;

    start = 0.0f;
    end = 200.0f;

    UILayerSetAnchorPoint(VIEW->layer, UIPointCreate(0.0f, 0.5f));

    UIAnimation radiusAnim;
    radiusAnim.finished = 0;
    radiusAnim.forKey = kUILayerKeyPositionX;
    radiusAnim.timingFunction = &UIAnimationTimingFunctionEaseInOutCubic;
    radiusAnim.startValue = &start;
    radiusAnim.endValue = &end;
    radiusAnim.startTime = UIAnimationGetCurrentTime();
    radiusAnim.endTime = UIAnimationGetCurrentTime() + 2500;
    radiusAnim._valueSize = sizeof(UIFloat);
    radiusAnim.duration = 2500;
    UILayerAddAnimation(VIEW->layer, radiusAnim);

    // start = VIEW->frame.size.width;
    // end = newRect.size.width;
    // radiusAnim.forKey = kUILayerKeyBoundsWidth;
    // UILayerAddAnimation(VIEW->layer, radiusAnim);

    // start = VIEW->frame.size.height;
    // end = newRect.size.height;
    // radiusAnim.forKey = kUILayerKeyBoundsHeight;
    // UILayerAddAnimation(VIEW->layer, radiusAnim);
}

void windowDidLoad(void *self, UIWindow window)
{
    printf("THE WINDOW LOADED!\n");

    UIViewSetBackgroundColor(window->mainView, UIColorCreateRGBA(255, 255, 255, 204));

    // UIRect rect1 = UIRectCreate(50, 50, 128, 128);
    // UIView view1 = UIViewCreate(rect1, rect1);

    // UIRect rect2 = UIRectCreate(200, 200, 128, 128);
    // UIView view2 = UIViewCreate(rect2, rect2);

    // UIPoint tap = UIPointCreate(10, 10);
    // UIPoint convertedTap = UIViewConvertPoint(view1, view2, tap);

    // printf("Converted tap: x(%f) y(%f)\n", convertedTap.x, convertedTap.y);

    UIRect myRect = UIRectCreate(224, 0, window->mainView->frame.size.width - 224, window->mainView->frame.size.height);
    UIView testView = UIViewCreate(myRect, myRect);
    VIEW = testView;

    testView->responder->leftMouseDown = &onViewClick;

    UIViewSetBackgroundColor(testView, UIColorCreateRGBA(255, 255, 255, 255));
    UIViewSetCornerRadius(testView, 0.0f);
    UIViewSetShadowColor(testView, UIColorCreateRGBA(0, 0, 0, 28));
    UIPoint shadowOffset = {
        .x = -4.0f,
        .y = 0};
    UIViewSetShadowOffset(testView, shadowOffset);
    UIViewSetShadowRadius(testView, 12.0f);
    UIViewAddSubview(window->mainView, testView);

    UIView windowActions = WindowActionsViewCreate();
    UIViewAddSubview(window->mainView, windowActions);
    UIViewSetCornerRadius(windowActions, 0.0f);
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