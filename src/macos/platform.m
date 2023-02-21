#include "../platform.h"
#include "../UIWindow.h"
#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSUserNotificationCenterDelegate>
@end

@implementation AppDelegate

@end

void _UIPlatformMain(UIApplication *application)
{
	[NSApplication sharedApplication];
	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
	[NSApp setPresentationOptions:NSApplicationPresentationDefault];
	[NSApp activateIgnoringOtherApps:YES];

	AppDelegate *delegate = [[AppDelegate alloc] init];
	[NSApp setDelegate:delegate];
	[NSApp finishLaunching];
}

void _UIPlatformEventLoop(UIApplication *application)
{
	@autoreleasepool
	{
		NSEvent *ev;
		do
		{
			ev = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
			if (ev)
			{
				// handle events here
				// NSLog(@"%@", ev);
				// [NSApp sendEvent:ev];
			}
		} while (ev);
	}
}

void _UIPlatformWindowCreate(UIWindow *window)
{
	NSWindow *myWindow;	 // typed pointer to NSWindow object
	NSView *myView;		 // typed pointer to NSView object
	NSRect graphicsRect; // contains an origin, width, height

	// initialize the rectangle variable
	graphicsRect = NSMakeRect(0.0, window->frame.height, window->frame.width, window->frame.height);

	myWindow = [[NSWindow alloc] // create the window
		initWithContentRect:graphicsRect
				  styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable
					backing:NSBackingStoreBuffered
					  defer:NO];

	myView = [[[NSView alloc] initWithFrame:graphicsRect] autorelease];

	[myWindow setContentView:myView]; // set window's view

	//   [myWindow setDelegate:myView]; // set window's delegate
	[myWindow makeKeyAndOrderFront:nil]; // display window

	window->platformWindow = myWindow;
}
void _UIPlatformWindowDestroy(UIWindow *window)
{
}

void _UIPlatformWindowSetTitle(UIWindow *window, const char *title)
{
	NSWindow *nsWindow = (NSWindow *)window->platformWindow;
	[nsWindow setTitle:[NSString stringWithUTF8String:title]];
}
void _UIPlatformWindowRender(UIWindow *window)
{
}