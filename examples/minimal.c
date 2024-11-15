#include "PanosUI.h"
#include "UIView.h"
#include "UIWindow.h"
#include "include/UIColor.h"
#include "include/UIEventResponder.h"
#include "include/UIGeometry.h"
#include "include/UISwitch.h"
#include "include/UIView.h"
#include <stdio.h>

UIView *WindowActionButtonCreate(UIFloat x, UIColor *bg)
{
	UIRect f = UIRectCreate(x, 0, 14, 14);
	UIView *button = UIViewCreate(f, f);

	UIViewSetCornerRadius(button, 5.0f);
	UIViewSetBackgroundColor(button, bg);

	return button;
}

void OnMinimize(UIEventResponder *self, UIEvent event)
{
	UIView *view = (UIView *)self->_self;
	printf("Minimized button clicked!\n");
	printf("Extra printf function because why not.\n");
}

UIView *WindowActionsViewCreate()
{
	UIRect rootFrame = UIRectCreate(14.0f, 16.0f, 58, 14);
	UIView *root = UIViewCreate(rootFrame, rootFrame);

	UIViewSetBackgroundColor(root, UIColorCreateRGBA(255, 0, 0, 0));

	UIViewAddSubview(root, WindowActionButtonCreate(0.0f, UIColorCreateRGBA(107, 122, 255, 255)));
	UIView *minimize = WindowActionButtonCreate(22.0f, UIColorCreateRGBA(149, 160, 178, 204));
	UIViewGetResponder(minimize)->leftMouseDown = &OnMinimize;
	UIViewAddSubview(root, minimize);
	UIViewAddSubview(root, WindowActionButtonCreate(44.0f, UIColorCreateRGBA(149, 160, 178, 204)));

	return root;
}

UIView *VIEW;

void onViewClick(UIEventResponder *self, UIEvent event)
{
	printf("On Click\n");
	UIFloat start, end;

	start = 0.0f;
	end = 200.0f;

	UIAnimation radiusAnim;
	radiusAnim.finished = 0;
	radiusAnim.timingFunction = &UIAnimationTimingFunctionEaseInOutCubic;
	radiusAnim.startValue = &start;
	radiusAnim.endValue = &end;
	radiusAnim.startTime = UIAnimationGetCurrentTime();
	radiusAnim.endTime = UIAnimationGetCurrentTime() + 2500;
	radiusAnim._valueSize = sizeof(UIFloat);
	radiusAnim.duration = 2500;

	start = UIViewGetFrame(VIEW).size.width;
	end = 64.0f;
	radiusAnim.forKey = kUILayerKeyBoundsWidth;
	UILayerAddAnimation(UIViewGetLayer(VIEW), radiusAnim);

	start = UIViewGetFrame(VIEW).size.height;
	end = 48.0f;
	radiusAnim.forKey = kUILayerKeyBoundsHeight;
	UILayerAddAnimation(UIViewGetLayer(VIEW), radiusAnim);
}

UIView *testView;
void MainViewLayoutSubviews(UIView *main)
{
	UIRect myRect = UIRectCreate(224, 0, UIViewGetFrame(main).size.width - 224, UIViewGetFrame(main).size.height);
	UIViewSetFrame(testView, myRect);
	main->needsLayout = 0;
	main->needsDisplay = 1;
}

void windowDidLoad(void *self, UIWindow *window)
{
	printf("THE WINDOW LOADED!\n");

	UIView *windowView = UIWindowGetMainView(window);
	UIViewSetLayoutSubviews(windowView, &MainViewLayoutSubviews);

	UIViewSetBackgroundColor(windowView, UIColorCreateRGBA(255, 255, 255, 204));

	UIRect myRect =
		UIRectCreate(224, 0, UIViewGetFrame(windowView).size.width - 224, UIViewGetFrame(windowView).size.height);

	testView = UIViewCreate(myRect, myRect);
	VIEW = testView;

	testView->responder->leftMouseDown = &onViewClick;

	UIViewSetBackgroundColor(testView, UIColorCreateRGBA(255, 255, 255, 255));
	UIViewSetCornerRadius(testView, 0.0f);
	UIViewSetShadowColor(testView, UIColorCreateRGBA(0, 0, 0, 28));
	UIPoint shadowOffset = {.x = -4.0f, .y = 0};
	UIViewSetShadowOffset(testView, shadowOffset);
	UIViewSetShadowRadius(testView, 12.0f);
	UIViewAddSubview(windowView, testView);

	UIView *windowActions = WindowActionsViewCreate();
	UIViewAddSubview(windowView, windowActions);
	UIViewSetCornerRadius(windowActions, 0.0f);

	UILabel *label = UILabelCreate(UIRectCreate(14, 56, 200, 200));
	UILabelSetContents(label, "QUICK ACCESS");
	UILabelSetFontSize(label, 12);
	UIViewSetBackgroundColor((UIView *)label, UIColorCreateRGBA(0, 0, 0, 0));
	UIViewAddSubview(windowView, (UIView *)label);

	UISwitch *s = UISwitchCreate(UIRectCreate(12, 12, 0, 0));
	UIViewAddSubview(testView, s);
}

void didFinishLaunching(UIApplication *application)
{
	UIRect windowFrame = UIRectCreate(0, 0, 718, 470);
	UIWindow *window = UIWindowCreate(windowFrame);

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