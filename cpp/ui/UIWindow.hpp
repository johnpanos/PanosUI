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

// typedef void (*callback_t)(UIViewController *self);

namespace UI
{
    // class WindowController
    // {
    // public:
    //     UIWindowController backing_window_controller;

    //     WindowController()
    //     {
    //         this->backing_window_controller = UIWindowControllerCreate();
    //         Callback<void(UIWindowController self)>::func = std::bind(&WindowController::_on_window_load, this, std::placeholders::_1);
    //         callback_t func = static_cast<callback_t>(Callback<void(UIWindowController * self)>::callback);
    //         UIWindowControllerSetOnWindowLoad(this->backing_window_controller, (onWindowLoad)func);
    //     }

    //     void _on_window_load(UIWindowController self)
    //     {
    //         this->on_window_load();
    //     }

    //     virtual void on_window_load()
    //     {
    //     }

    //     virtual ~WindowController()
    //     {
    //         UIWindowControllerDestroy(this->backing_window_controller);
    //     }
    // };

    class Window
    {
    private:
        UIWindow backing_window;

    public:
        Window(UIRect frame)
        {
            this->backing_window = UIWindowCreate(frame);
        }

        ~Window()
        {
            UIWindowDestroy(this->backing_window);
        }

        void show() {
            UIWindowShow(this->backing_window);
        }

        void set_title(std::string title)
        {
            UIWindowSetTitle(this->backing_window, title.c_str());
        }
    };
};

#endif