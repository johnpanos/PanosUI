#ifndef _UIWINDOW_HPP
#define _UIWINDOW_HPP

#include <stdio.h>
#include <functional>
#include "UIWindow.h"
#include "UIViewController.h"
#include "UIView.hpp"

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

typedef void (*callback_t)(UIViewController *self);

namespace UI
{
    class ViewController
    {
    public:
        UIViewController *backing_view_controller;
        UI::View view;

        ViewController()
        {
            this->backing_view_controller = UIViewControllerCreate();
            Callback<void(UIViewController * self)>::func = std::bind(&ViewController::_view_did_load, this, std::placeholders::_1);
            callback_t func = static_cast<callback_t>(Callback<void(UIViewController * self)>::callback);
            this->backing_view_controller->viewDidLoad = func;
        }

        virtual void load_view()
        {
            this->backing_view_controller->loadView(this->backing_view_controller);
        }

        void _view_did_load(UIViewController *viewController)
        {
            this->view = View(viewController->view);
            this->view_did_load();
        }

        virtual void view_did_load()
        {
        }

        virtual ~ViewController()
        {
            UIViewControllerDestroy(this->backing_view_controller);
        }
    };

    class Window
    {
    private:
        UIWindow *backing_window;

    public:
        Window(UIRect frame)
        {
            this->backing_window = UIWindowCreate(frame);
        }

        ~Window()
        {
            UIWindowDestroy(this->backing_window);
        }

        void set_title(std::string title)
        {
            UIWindowSetTitle(this->backing_window, title.c_str());
        }

        void set_view_controller(UI::ViewController *view_controller)
        {
            UIWindowSetRootViewController(this->backing_window, view_controller->backing_view_controller);
        }
    };
};

#endif