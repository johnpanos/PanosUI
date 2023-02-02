#include <stdlib.h>
#include "UIApplication.h"

UIApplication_t sharedApplication;

void UIApplicationMain(UIApplicationDelegate_t delegate) {
    sharedApplication = malloc(sizeof(UIApplication));
    sharedApplication->running = 1;
    sharedApplication->delegate = delegate;

    _UIPlatformMain(sharedApplication);

    delegate->didFinishLaunching(sharedApplication);

    UIApplicationRun();
}

void UIApplicationRun() {
    while (sharedApplication->running) {
        _UIPlatformEventLoop(sharedApplication);
    }
}

UIApplication UIApplicationShared() {
    return sharedApplication;
}