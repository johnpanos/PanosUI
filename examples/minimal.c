#include <stdio.h>
#include "PanosUI.h"

void windowDidLoad(UIWindow window)
{
    printf("THE WINDOW LOADED!\n");
}

void CreateMacOSWindow()
{
    UIRect window_frame = {
        .x = 0,
        .y = 0,
        .width = 100,
        .height = 100};
    UIWindow window = UIWindowCreate(window_frame);

    UIWindowController myWindowController = UIWindowControllerCreate();
    myWindowController->windowDidLoad = &windowDidLoad;

    window->controller = myWindowController;

    UIWindowShow(window);
    UIWindowSetTitle(window, "C Example");

    UIColor bg = {.r = 246, .g = 246, .b = 246, .a = 255};
    window->mainView->backgroundColor = bg;
}

void didFinishLaunching(UIApplication *application)
{
    // CreateMacOSWindow();
    CreateMacOSWindow();
}

static UIApplicationDelegate my_delegate = {
    .didFinishLaunching = &didFinishLaunching};

int main()
{
    UIApplicationMain(&my_delegate);
}