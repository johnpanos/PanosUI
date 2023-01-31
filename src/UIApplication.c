#include <stdlib.h>
#include "UIApplication.h"

UIApplication *sharedApplication;

void UIApplicationMain(UIApplicationDelegate *delegate) {
    sharedApplication = malloc(sizeof(UIApplication));
    sharedApplication->running = 1;

    _UIPlatformMain(sharedApplication);

    delegate->didFinishLaunching(sharedApplication);

    UIApplicationRun();
}

void UIApplicationRun() {
    while (sharedApplication->running) {
        _UIPlatformEventLoop(sharedApplication);
    }
}

UIApplication *UIApplicationShared() {
    return sharedApplication;
}