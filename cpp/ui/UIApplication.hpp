#ifndef _UI_APPLICATION_HPP
#define _UI_APPLICATION_HPP
#include <iostream>

extern "C"
{
#include "UIApplication.h"
#include "UIView.h"
#include "UIWindow.h"
}

namespace UI
{
class ApplicationDelegate
{
  public:
	virtual ~ApplicationDelegate(){};

	virtual void did_finish_launching()
	{
	}
};

class Application
{
  private:
	static void did_finish_launching_wrapper(UIApplication *application)
	{
		Application::applicationDelegate->did_finish_launching();
	}

  public:
	inline static ApplicationDelegate *applicationDelegate;
	static void main(ApplicationDelegate *applicationDelegate)
	{
		UIApplicationDelegate delegate;
		delegate.didFinishLaunching = &Application::did_finish_launching_wrapper;

		Application::applicationDelegate = applicationDelegate;

		UIApplicationMain(&delegate);
	};
};
}; // namespace UI

#endif