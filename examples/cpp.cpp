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
                            UI::Animation<int>::create(2000, kUILayerKeyPositionX, &UIAnimationTimingFunctionEaseInOutQuart, 0, 100));
        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<int>::create(2000, kUILayerKeyPositionY, &UIAnimationTimingFunctionEaseInOutQuart, 0, 100));
        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<float>::create(2000, kUILayerKeyCornerRadius, &UIAnimationTimingFunctionEaseInOutQuart, 0.0f, 100.0f));
        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<float>::create(2000, kUILayerKeyShadowRadius, &UIAnimationTimingFunctionEaseInOutQuart, 0.0f, 8.0f));
    }
};

class MyDelegate : public UI::ApplicationDelegate
{
    virtual void did_finish_launching()
    {
        MyWindowController *window_controller = new MyWindowController();

        UI::Window *window = new UI::Window(
            UIRectCreate(0, 0, 500, 500));

        window->set_controller(window_controller);
        window->show();
        window->set_title("cereal");
    }
};

int main()
{
    UI::Application::main(new MyDelegate());
}