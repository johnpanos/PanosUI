#include "UIWindow.h"
#include "include/UIColor.h"
#include "include/UIView.h"
#include "include/UIWindowController.h"
#include <stdio.h>
#include <stdlib.h>

UIView *_UIWindowCreateFrameView(UIWindow *window)
{
	UIRect titlebarFrame = UIRectCreate(8, 8, UIRectGetWidth(window->frame), 28);
	UIView *titlebar = UIViewCreate(titlebarFrame, titlebarFrame);
	UIViewSetBackgroundColor(titlebar, UIColorCreateRGBA(255, 255, 255, 255));
	UIViewSetCornerRadius(titlebar, 0.0f);

	UIViewSetBorderColor(titlebar, UIColorCreateRGBA(0, 0, 0, 50));
	UIViewSetBorderWidth(titlebar, 0.0f);

	UIRect redFrame = UIRectCreate(8, 8, 16, 16);
	UIColor *red = UIColorCreateRGBA(120, 27, 112, 255);
	UIView *redLight = UIViewCreate(redFrame, redFrame);
	UIViewSetCornerRadius(redLight, 12);
	UIViewSetBackgroundColor(redLight, red);
	UIViewSetBorderColor(redLight, UIColorCreateRGBA(0, 0, 0, 21));
	UIViewSetBorderWidth(redLight, 0.5f);

	UIRect yellowFrame = redFrame;
	yellowFrame.origin = UIPointOffset(yellowFrame.origin, 24, 0);
	UIColor *yellow = UIColorCreateRGBA(120, 27, 112, 100);
	UIView *yellowLight = UIViewCreate(yellowFrame, yellowFrame);
	UIViewSetCornerRadius(yellowLight, 12);
	UIViewSetBackgroundColor(yellowLight, yellow);
	UIViewSetBorderColor(yellowLight, UIColorCreateRGBA(0, 0, 0, 21));
	UIViewSetBorderWidth(yellowLight, 0.5f);

	UIRect greenFrame = yellowFrame;
	greenFrame.origin = UIPointOffset(greenFrame.origin, 24, 0);
	UIColor *green = UIColorCreateRGBA(120, 27, 112, 100);
	UIView *greenLight = UIViewCreate(greenFrame, greenFrame);
	UIViewSetCornerRadius(greenLight, 12);
	UIViewSetBackgroundColor(greenLight, green);
	UIViewSetBorderColor(greenLight, UIColorCreateRGBA(0, 0, 0, 21));
	UIViewSetBorderWidth(greenLight, 0.5f);

	UIViewAddSubview(titlebar, redLight);
	UIViewAddSubview(titlebar, yellowLight);
	UIViewAddSubview(titlebar, greenLight);

	titlebar->needsDisplay = 1;

	return titlebar;
}

#define INSET_AMOUNT 16.0f
UIWindow *UIWindowCreate(UIRect frame)
{
	UIWindow *window = calloc(1, sizeof(struct _UIWindow));

	window->responder = UIEventResponderCreate();

	ArrayAddValue(UIApplicationShared()->windows, window);

	window->frame = UIRectOutset(frame, INSET_AMOUNT, INSET_AMOUNT);
	window->frame.origin.x = 0;
	window->frame.origin.y = 0;
	window->contentFrame = frame;
	window->contentFrame.origin.x = 0;
	window->contentFrame.origin.y = 0;

	window->controller = UIWindowControllerGetDefault();

	window->mainView = UIViewCreate(frame, frame);
	UIViewSetBackgroundColor(window->mainView, UIColorCreateRGBA(255, 255, 255, 255));
	window->frameView = _UIWindowCreateFrameView(window);

	return window;
}

UIWindow *UIWindowCreateWithFlags(UIRect frame, unsigned int flags)
{
	UIWindow *window = UIWindowCreate(frame);
	window->windowFlags = flags;
	return window;
}

void UIWindowShow(UIWindow *window)
{
	window->controller->windowWillLoad(window->controller->_self, window);

	_UIPlatformWindowCreate(window);

	window->controller->windowDidLoad(window->controller->_self, window);
}

void UIWindowDestroy(UIWindow *window)
{
	_UIPlatformWindowDestroy(window);

	ArrayRemoveValueByRef(UIApplicationShared()->windows, window);

	free(window);
}

void UIWindowSetTitle(UIWindow *window, const char *title)
{
	window->title = title;
	if (window->platformWindow != NULL)
	{
		_UIPlatformWindowSetTitle(window, title);
	}
}

UIView *UIWindowGetMainView(UIWindow *window)
{
	return window->mainView;
}

void UIWindowSetController(UIWindow *window, UIWindowController *controller)
{
	window->controller = controller;
}

void RENDER_SUBVIEWS(UIView *view, UIGraphicsContext *context)
{
	UIGraphicsContextSave(context);
	{
		UILayer layer = UILayerGetInFlight(view->layer);

		UIGraphicsContextSave(context);
		{
			UIGraphicsContextSetTransform(context, layer.frame.origin.x, layer.frame.origin.y);
			UILayerRenderInContext(&layer, context);
			UIGraphicsContextSetTransform(context, layer.bounds.origin.x, layer.bounds.origin.y);

			ArrayForEach(UIView * viewToRender, view->subviews)
			{
				RENDER_SUBVIEWS(viewToRender, context);
			}
		}
		UIGraphicsContextRestore(context);
	}
	UIGraphicsContextRestore(context);
}

void _UIWindowLayoutPhase_UIViewLayout(UIView *viewToLayout)
{
	if (viewToLayout->needsLayout)
	{
		viewToLayout->layoutSubviews(viewToLayout);
	}

	ArrayForEach(UIView * child, viewToLayout->subviews)
	{
		_UIWindowLayoutPhase_UIViewLayout(child);
	}
}

int _UIWindowRenderPhase_ShouldRender(UIView *view)
{
	if (ArrayGetCapacity(view->layer->animations) > 0 || view->needsDisplay)
	{
		view->needsDisplay = 0;
		return 1;
	}

	else
	{
		ArrayForEach(UIView * child, view->subviews)
		{
			if (_UIWindowRenderPhase_ShouldRender(child) || child->needsDisplay)
			{
				child->needsDisplay = 0;
				return 1;
			}
		}
	}

	return 0;
}

void UIWindowUpdate(UIWindow *window)
{
	// printf("updating\n");
	UIView *rootView = window->mainView;

	_UIWindowLayoutPhase_UIViewLayout(rootView);

	int shouldRender = _UIWindowRenderPhase_ShouldRender(rootView);
	if (shouldRender)
	{
		_UIPlatformWindowMakeCurrent(window);
		UIGraphicsContextMakeCurrent(window->graphicsContext);
		UIGraphicsContextClear(window->graphicsContext);

		// Draw dropshadow
		UIGraphicsContextSave(window->graphicsContext);
		{
			UIGraphicsSetFillColor(window->graphicsContext, UIColorCreateRGBA(0, 0, 0, 61));
			UIGraphicsContextSetShadow(window->graphicsContext, UIPointCreate(0, 2), 8.0f);
			UIGraphicsContextAddRect(window->graphicsContext, UIRectOutset(window->contentFrame, 2.0f, 2.0f), 8.0f);
			UIGraphicsContextRestore(window->graphicsContext);

			// Clip all children to inside
			UIGraphicsContextClipToRect(window->graphicsContext, window->contentFrame, 8.0f);

			// Draw background
			// UIGraphicsSetFillColor(window->graphicsContext, window->mainView->backgroundColor);
			// UIGraphicsContextAddRect(window->graphicsContext, window->contentFrame, 8.0f);

			UIGraphicsContextSave(window->graphicsContext);
			{
				UIGraphicsContextSetTransform(window->graphicsContext, window->contentFrame.origin.x,
											  window->contentFrame.origin.y);
				UIGraphicsContextClipToRect(window->graphicsContext, window->mainView->frame, 0.0f);
				RENDER_SUBVIEWS(rootView, window->graphicsContext);

				// RENDER_SUBVIEWS(window->frameView, window->graphicsContext);
				rootView->needsDisplay = 0;
			}
			UIGraphicsContextRestore(window->graphicsContext);

			UIGraphicsSetStrokeColor(window->graphicsContext, UIColorCreateRGBA(0, 0, 0, 172));
			UIGraphicsSetStrokeWidth(window->graphicsContext, 0.5f);
			UIGraphicsContextAddRect(window->graphicsContext, window->contentFrame, 8.0f);
		}
		UIGraphicsContextRestore(window->graphicsContext);

		UIGraphicsContextFlush(window->graphicsContext);
		_UIPlatformWindowFlush(window);
	}
}

void UIWindowSendEvent(UIWindow *window, UIEvent event)
{
	if (event.type == UIEventTypeMouseMotion)
	{
		window->mousePos.x = ((UIFloat)event._eventData.mouseMotion.x) - window->contentFrame.origin.x;
		window->mousePos.y = ((UIFloat)event._eventData.mouseMotion.y) - window->contentFrame.origin.y;
	}

	UIRect dragger = UIRectCreate(window->contentFrame.size.width, window->contentFrame.size.height, 0, 0);
	dragger = UIRectOutset(dragger, 10, 10);

	// if ((window->mousePos.x > 0 && window->mousePos.x < window->frame.size.width) &&
	//     (window->mousePos.y > 0 && window->mousePos.y < 28))
	// {
	//     _UIPlatformWindowMove(window, event);
	// }
	// else if (UIPointInRect(window->mousePos, dragger))
	// {
	//     _UIPlatformWindowResize(window, event);
	// }
	// else
	// {
	UIPoint hitPoint = {.x = window->mousePos.x, .y = window->mousePos.y};
	UIView *hitView = UIViewHitTest(window->mainView, hitPoint);
	switch (event.type)
	{
	case UIEventTypeMouseDown:
		if (event._eventData.mouseButton.button == UIEventMouseButtonTypeLeft)
		{
			printf("hitview frame @ (%f, %f) : x(%f) y(%f) w(%f) h(%f)\n", hitPoint.x, hitPoint.y,
				   hitView->frame.origin.x, hitView->frame.origin.y, hitView->frame.size.width,
				   hitView->frame.size.height);
			hitView->responder->leftMouseDown(hitView->responder, event);
		}
		else if (event._eventData.mouseButton.button == UIEventMouseButtonTypeRight)
		{
			hitView->responder->rightMouseDown(hitView->responder, event);
		}
		break;
	case UIEventTypeMouseUp:
		if (event._eventData.mouseButton.button == UIEventMouseButtonTypeLeft)
		{
			hitView->responder->leftMouseUp(hitView->responder, event);
		}
		else if (event._eventData.mouseButton.button == UIEventMouseButtonTypeRight)
		{
			hitView->responder->rightMouseUp(hitView->responder, event);
		}
		break;
	case UIEventTypeMouseMotion:
		if (hitView != NULL)
		{
			hitView->responder->mouseMove(hitView->responder, event);
		}
		break;
	case UIEventTypeMouseDrag:
	case UIEventTypeMouseEntered:
	case UIEventTypeMouseScroll:
	case UIEventTypeKeyboardDown:
	case UIEventTypeKeyboardUp:
		break;
	};
	// }
}