#pragma once

#include <stdlib.h>
#include "UIWindow.h"

typedef struct _UIWindowController *UIWindowController;
typedef void (*onWindowLoad)(UIWindowController self);
// typedef void (*)

typedef struct _UIWindowController *UIWindowController;

UIWindowController UIWindowControllerCreate();
void UIWindowControllerDestroy(UIWindowController windowController);

// MARK: Lifecycle
void UIWindowControllerSetOnWindowLoad(UIWindowController windowController, onWindowLoad onLoad);
onWindowLoad UIWindowControllerGetOnWindowLoad(UIWindowController windowController);

UIWindow *UIWindowControllerGetWindow(UIWindowController windowController);