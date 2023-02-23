#include "PanosUI.h"
#include "UIView.h"
#include "UIWindow.h"
#include <stdio.h>

void windowDidLoad(void *self, UIWindow *window)
{
	UIView *view = UIWindowGetMainView(window);

	UIRect frameRect = UIRectCreate(0, 0, 200, 200);
	UIView *view2 = UIViewCreate(frameRect, frameRect);

	UIViewSetBackgroundColor(view2, UIColorCreateRGBA(0, 0, 0, 255));
	UILayerSetAnchorPoint(UIViewGetLayer(view2), UIPointCreate(0.25f, 0.25f));
	UIViewSetFrame(view2, UIRectCreate(10, 10, 750 - 20, 600 - 20));

	UIViewAddSubview(view, view2);

	UIFloat start = UIViewGetFrame(view2).size.width;
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

	UILayerAddAnimation(UIViewGetLayer(view2), radiusAnim);

	radiusAnim.forKey = kUILayerKeyBoundsHeight;
	start = UIViewGetFrame(view2).size.height;
	end = 50.0f;
	UILayerAddAnimation(UIViewGetLayer(view2), radiusAnim);

	radiusAnim.forKey = kUILayerKeyCornerRadius;
	start = 0.0f;
	end = 64.0f;
	UILayerAddAnimation(UIViewGetLayer(view2), radiusAnim);

	// UILabel *label = UILabelCreate(UIRectCreate(0, 0, 10, 10));
	// UIViewSetBackgroundColor((UIView *)label, UIColorCreateRGBA(0, 0, 255, 255));
	// UIViewAddSubview(view, (UIView *)label);

	// printf("w: %f\n", UIViewGetFrame((UIView *)label).size.width);
}

void didFinishLaunching(UIApplication *application)
{
	UIRect windowFrame = UIRectCreate(0, 0, 750, 600);
	UIWindow *window =
		UIWindowCreateWithFlags(windowFrame, UIWindowTypeHasClose | UIWindowTypeHasHide | UIWindowTypeHasResize);

	UIWindowController *myWindowController = UIWindowControllerCreate();
	myWindowController->windowDidLoad = &windowDidLoad;

	UIWindowSetController(window, myWindowController);

	UIWindowShow(window);
	UIWindowSetTitle(window, "C Example");
}

static UIApplicationDelegate my_delegate = {.didFinishLaunching = &didFinishLaunching};

int main()
{
	UIApplicationMain(&my_delegate);
}