#include <stdio.h>
#include "PanosUI.h"

void didFinishLaunching(UIApplication *application)
{
    UIRect window_frame = {
        .x = 0,
        .y = 0,
        .width = 300,
        .height = 300};
    UIWindow window = UIWindowCreate(window_frame);
    UIWindowSetTitle(window, "C Example");
}

static UIApplicationDelegate my_delegate = {
    .didFinishLaunching = &didFinishLaunching};

int main()
{
    UIApplicationMain(&my_delegate);
}