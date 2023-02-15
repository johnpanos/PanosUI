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

    UI::View *detail_view;

    virtual void window_did_load()
    {
        std::cout << "Window did load from C++\n";
        this->window->root_view = new UI::View(this->window->backing_window->mainView);

        // UIRect detail_view_frame = UIRectCreate(224, 0, this->window->get_root_view()->get_frame().size.width - 224, this->window->get_root_view()->get_frame().size.height);
        // this->detail_view = new UI::View(detail_view_frame, detail_view_frame);
        // this->detail_view->set_shadow_offset(UIPointCreate(-4.0f, 0.0f));
        // this->detail_view->set_shadow_radius(12.0f);
        // this->detail_view->set_shadow_color(UIColorCreateRGBA(0, 0, 0, 28));
        // this->detail_view->set_background_color(UIColorCreateRGBA(255, 255, 255, 255));

        UIRect my_view_frame = UIRectCreate(100, 100, 200, 200);
        this->my_view = new MyView(my_view_frame, my_view_frame);

        this->window->get_root_view()->add_subview(this->my_view);

        this->my_view->set_background_color(UIColorCreateRGBA(0, 255, 0, 255));
        // UILayerAddAnimation(this->my_view->backing_view->layer,
        //                     UI::Animation<float>::create(
        //                         5000,
        //                         kUILayerKeyBoundsWidth,
        //                         &UIAnimationTimingFunctionEaseInOutCubic,
        //                         200.0f, 400.0f));
        UILayerAddAnimation(this->my_view->backing_view->layer,
                            UI::Animation<float>::create(
                                5000,
                                kUILayerKeyBoundsHeight,
                                &UIAnimationTimingFunctionEaseOutBounce,
                                200.0f, 350.0f));

        // UILayerAddAnimation(this->my_view->backing_view->layer,
        //                     UI::Animation<float>::create(
        //                         5000,
        //                         kUILayerKeyCornerRadius,
        //                         &UIAnimationTimingFunctionEaseInOutCubic,
        //                         0.0f, 100.0f));
        this->my_view->set_corner_radius(100.0f);

        // UIRect view2_frame = UIRectCreate(0, 0, 50, 50);
        // view2 = new UI::View(view2_frame, view2_frame);
        // this->my_view->add_subview(view2);
        // view2->set_background_color(UIColorCreateRGBA(0, 0, 0, 255));
        // UILayerAddAnimation(this->view2->backing_view->layer,
        //                     UI::Animation<float>::create(
        //                         5000,
        //                         kUILayerKeyPositionY,
        //                         &UIAnimationTimingFunctionEaseInOutCubic,
        //                         200.0f, 0.0f));
        // UILayerAddAnimation(this->view2->backing_view->layer,
        //                     UI::Animation<float>::create(
        //                         5000,
        //                         kUILayerKeyCornerRadius,
        //                         &UIAnimationTimingFunctionEaseInOutCubic,
        //                         100.0f, 0.0f));
        // UILayerAddAnimation(this->view2->backing_view->layer,
        //                     UI::Animation<float>::create(
        //                         5000,
        //                         kUILayerKeyBoundsWidth,
        //                         &UIAnimationTimingFunctionEaseInOutCubic,
        //                         0.0f, 200.0f));

        // this->window->get_root_view()->add_subview(this->detail_view);
    }
};

class MyDelegate : public UI::ApplicationDelegate
{
    virtual void did_finish_launching()
    {
        MyWindowController *window_controller = new MyWindowController();

        UI::Window *window = new UI::Window(
            UIRectCreate(0, 0, 750, 600));

        window->set_controller(window_controller);
        window->show();
        window->set_title("C++ Window");
    }
};

int main()
{
    UI::Application::main(new MyDelegate());
}