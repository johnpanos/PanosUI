#include <stdio.h>
#include <iostream>
#include "ui/UIApplication.hpp"
#include "ui/UIWindow.hpp"

class MyWindowController : public UI::WindowController {
    UI::View *my_view;

    virtual void window_did_load() {
        std::cout << "Window did load from C++\n";

        UIRect my_view_frame = UIRectCreate(100, 100, 200, 200);
        this->my_view = new UI::View(my_view_frame, my_view_frame);
        this->my_view->set_background_color(UIColorCreateRGBA(255, 0, 0, 255));
        this->window->get_root_view()->add_subview(this->my_view);
    }
};

class MyDelegate : public UI::ApplicationDelegate
{
    virtual void did_finish_launching()
    {
        MyWindowController *window_controller = new MyWindowController();

        UI::Window *window = new UI::Window(
            UIRectCreate(0, 0, 1000, 500)
        );

        window->set_controller(window_controller);
        window->show();
        window->set_title("cereal");
    }
};

int main()
{
    UI::Application::main(new MyDelegate());
}