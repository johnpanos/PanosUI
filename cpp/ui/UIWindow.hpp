#ifndef _UIWINDOW_HPP
#define _UIWINDOW_HPP

#include <stdio.h>
#include <functional>
#include "Callback.hpp"

extern "C"
{
#include "UIWindow.h"
#include "UIWindowController.h"
#include "UIView.hpp"
}

typedef void (*window_callback_t)(void*self,UIWindow window);

namespace UI
{
    class Window;

    class WindowController
    {
    public:
        UIWindowController backing_window_controller;
        UI::Window *window;

        WindowController()
        {
            this->backing_window_controller = UIWindowControllerCreate();
            Callback<void(UIWindow window)>::func = std::bind(&WindowController::_window_did_load, this, std::placeholders::_1);
            this->backing_window_controller->windowDidLoad = static_cast<window_callback_t>(Callback<void(void *self, UIWindow window)>::callback);
        }

        void _window_did_load(UIWindow window)
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
        UI::WindowController *controller;

    public:
        UIWindow backing_window;
        UI::View *root_view;

        Window(UIRect frame)
        {
            this->backing_window = UIWindowCreate(frame);
            this->root_view = nullptr;
        }

        ~Window()
        {
            UIWindowDestroy(this->backing_window);
        }

        void set_controller(UI::WindowController *controller)
        {
            this->controller = controller;
            this->controller->window = this;
            this->backing_window->controller = controller->backing_window_controller;
        }

        void show()
        {
            UIWindowShow(this->backing_window);
        }

        void set_title(std::string title)
        {
            UIWindowSetTitle(this->backing_window, title.c_str());
        }

        UI::View *get_root_view()
        {
            return this->root_view;
        }
    };
};

#endif