#ifndef _UIWINDOW_HPP
#define _UIWINDOW_HPP

#include <stdio.h>
#include <functional>

extern "C"
{
#include "UIWindow.h"
#include "UIWindowController.h"
#include "UIView.hpp"
}

template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)>
{
    template <typename... Args>
    static Ret callback(Args... args)
    {
        return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

typedef void (*callback_t)(UIWindow window);

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
            this->backing_window_controller->windowDidLoad = static_cast<callback_t>(Callback<void(UIWindow window)>::callback);
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
        UIWindow backing_window;
        UI::WindowController *controller;
        UI::View *root_view;

    public:
        Window(UIRect frame)
        {
            this->backing_window = UIWindowCreate(frame);
            this->root_view = new UI::View(this->backing_window->mainView);
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