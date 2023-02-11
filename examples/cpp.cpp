#include <stdio.h>
#include <iostream>
#include "ui/UIApplication.hpp"
#include "ui/UIWindow.hpp"
#include "ui/UIAnimation.hpp"

class MyView : public UI::View
{
    using UI::View::View;

    virtual void leftMouseDown(UIEvent event)
    {
        std::cout << "On click from C++!\n";
    }
};

class MyWindowController : public UI::WindowController
{
    MyView *my_view;
    UI::View *view2;

    virtual void window_did_load()
    {
        std::cout << "Window did load from C++\n";

        UIRect my_view_frame = UIRectCreate(0, 0, 200, 200);
        this->my_view = new MyView(my_view_frame, my_view_frame);

        this->my_view->set_background_color(UIColorCreateRGBA(0, 255, 0, 255));
        this->my_view->set_corner_radius(0.0f);

        this->window->get_root_view()->add_subview(this->my_view);

        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<int>::create(
                                1000,
                                kUILayerKeyPositionX,
                                &UIAnimationTimingFunctionEaseInOutCirc,
                                0, 500));
        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<int>::create(
                                1000,
                                kUILayerKeyPositionY,
                                &UIAnimationTimingFunctionEaseInOutCirc,
                                0, 100));
        this->my_view->set_frame(UIRectCreate(100, 100, 200, 200));

        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<float>::create(
                                1000,
                                kUILayerKeyCornerRadius,
                                &UIAnimationTimingFunctionEaseInOutCirc,
                                0.0f, 100.0f));
        this->my_view->set_corner_radius(100.0f);

        UIRect view2_frame = UIRectCreate(0, 0, 50, 50);
        view2 = new UI::View(view2_frame, view2_frame);
        view2->set_background_color(UIColorCreateRGBA(0, 0, 0, 255));
        UILayerAddAnimation(this->view2->backing_view->layer,
                            UI::Animation<float>::create(
                                1000,
                                kUILayerKeyCornerRadius,
                                &UIAnimationTimingFunctionEaseInOutCirc,
                                0.0f, 2.0f));
        this->my_view->add_subview(view2);
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