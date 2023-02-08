#include <stdlib.h>
#include <stdio.h>
#include "UIApplication.h"

UIApplication *sharedApplication;

void UIApplicationMain(UIApplicationDelegate *delegate)
{
    sharedApplication = malloc(sizeof(struct _UIApplication));
    sharedApplication->running = 1;
    sharedApplication->delegate = delegate;
    sharedApplication->windows = ArrayCreate(sizeof(UIWindow));

    _UIPlatformMain(sharedApplication);

    delegate->didFinishLaunching(sharedApplication);

    UIApplicationRun();
}

void UIApplicationRun()
{
    while (sharedApplication->running)
    {
        _UIPlatformEventLoop(sharedApplication);
    }
}

UIApplication *UIApplicationShared()
{
    return sharedApplication;
}

void UIApplicationSendEvent(UIEvent event) {
    // printf("Event type: %d (%p)\n", event.type, event.window);

    // if (event.type == UIEventTypeMouseMotion) {
    //     printf("x: %d | y: %d\n", event._eventData.mouseMotion.x, event._eventData.mouseMotion.y);
    // } else if (event.type == UIEventTypeMouseScroll) {
    //     if (event._eventData.mouseScroll.direction == UIEventMouseScrollDirectionVertical) {
    //         printf("y: %d\n", event._eventData.mouseScroll.y);
    //     } else {
    //         printf("x: %d\n", event._eventData.mouseScroll.x);
    //     }
    // } else if (event.type == UIEventTypeMouseDown) {
    //     printf("CLICK\n");
    // }

    UIWindowSendEvent(event.window, event);
}