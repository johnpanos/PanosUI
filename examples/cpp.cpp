#include <stdio.h>
#include <iostream>
#include "ui/UIApplication.hpp"
#include "ui/UIWindow.hpp"
#include "ui/UIAnimation.hpp"

class MyWindowController : public UI::WindowController
{
    UI::View *my_view;

    virtual void window_did_load()
    {
        std::cout << "Window did load from C++\n";

        UIRect my_view_frame = UIRectCreate(0, 0, 200, 200);
        this->my_view = new UI::View(my_view_frame, my_view_frame);

        this->my_view->set_background_color(UIColorCreateRGBA(255, 0, 0, 255));
        this->my_view->set_corner_radius(0.0f);

        this->my_view->set_shadow_color(UIColorCreateRGBA(0, 0, 0, 31));
        this->my_view->set_shadow_offset(UIPointCreate(10, 10));
        this->my_view->set_shadow_radius(0.0f);

        this->window->get_root_view()->add_subview(this->my_view);

        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<int>::create(4000, kUILayerKeyPositionX, &UIAnimationTimingFunctionEaseOutBounce, 0, 100));
        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<int>::create(4000, kUILayerKeyPositionY, &UIAnimationTimingFunctionEaseOutBounce, 0, 100));
        this->my_view->set_frame(UIRectCreate(100, 100, 200, 200));
        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<float>::create(4000, kUILayerKeyCornerRadius, &UIAnimationTimingFunctionEaseOutBounce, 0.0f, 100.0f));
        this->my_view->set_corner_radius(100.0f);
        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<float>::create(4000, kUILayerKeyShadowRadius, &UIAnimationTimingFunctionEaseOutBounce, 0.0f, 8.0f));
        this->my_view->set_shadow_radius(8.0f);
    }
};

class MyDelegate : public UI::ApplicationDelegate
{
    virtual void did_finish_launching()
    {
        MyWindowController *window_controller = new MyWindowController();

        UI::Window *window = new UI::Window(
            UIRectCreate(0, 0, 425, 425));

        window->set_controller(window_controller);
        window->show();
        window->set_title("C++ Window");
    }
};

int main()
{
    UI::Application::main(new MyDelegate());
}