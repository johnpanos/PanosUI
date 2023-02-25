#include "PanosUI.h"
#include <stdlib.h>

void didFinishLaunching(UIApplication *application)
{
	exit(0);
}

static UIApplicationDelegate my_delegate = {.didFinishLaunching = &didFinishLaunching};

int main()
{
	UIApplicationMain(&my_delegate);
	return 1;
}