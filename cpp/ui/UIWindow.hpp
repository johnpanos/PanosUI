#ifndef _UIWINDOW_HPP
#define _UIWINDOW_HPP

#include "Callback.hpp"
#include <functional>
#include <stdio.h>
#include <string>

#include "../PanosUI.hpp"
#include "UIView.hpp"
#include "UIWindow.h"

typedef void (*window_callback_t)(void *self, UIWindow *window);

namespace UI
{
class Window;

class WindowController
{
  public:
	UIWindowController *backing_window_controller;
	UI::Window *window;

	WindowController()
	{
		this->backing_window_controller = UIWindowControllerCreate();
		Callback<void(void *self, UIWindow *window)>::func =
			std::bind(&WindowController::_window_did_load, this, std::placeholders::_1, std::placeholders::_2);
		this->backing_window_controller->windowDidLoad =
			static_cast<window_callback_t>(Callback<void(void *self, UIWindow *window)>::callback);
	}

	void _window_did_load(void *self, UIWindow *window)
	{
		this->window_did_load();
	}

	virtual void window_did_load()
	{
	}

	virtual ~WindowController()
	{
		UIWindowControllerDestroy(this->backing_window_controller);
	}
};

class Window
{
  private:
	UIWindow *backing_window;

	UI::WindowController *controller;
	UI::View *main_view;

  public:
	Window(UIRect frame)
	{
		this->backing_window = UIWindowCreate(frame);
		this->main_view = new UI::View(UIWindowGetMainView(this->backing_window));
	}

	~Window()
	{
		UIWindowDestroy(this->backing_window);
	}

	void set_controller(UI::WindowController *controller)
	{
		this->controller = controller;
		this->controller->window = this;
		UIWindowSetController(this->backing_window, this->controller->backing_window_controller);
	}

	void show()
	{
		UIWindowShow(this->backing_window);
	}

	void set_title(std::string title)
	{
		UIWindowSetTitle(this->backing_window, title.c_str());
	}

	UI::View *get_main_view()
	{
		return this->main_view;
	}
};
}; // namespace UI

#endif