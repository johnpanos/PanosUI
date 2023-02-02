#include <stdio.h>
#include <iostream>
#include "ui/UIApplication.hpp"
#include "ui/UIWindow.hpp"

class MyViewController : public UI::ViewController
{
    virtual void view_did_load()
    {
        std::cout << "View did load from C++!\n";

        UIRect rect;
        rect.x = 0;
        rect.y = 0;
        rect.width = 100;
        rect.height = 100;

        UI::View *my_view = new UI::View(rect, rect);
        this->view.add_subview(my_view);

        std::cout << "Frame width: " << this->view.get_frame().width << "\n";
        std::cout << "Frame height: " << this->view.get_frame().height << "\n";
    }
};

class MyDelegate : public UI::ApplicationDelegate
{
    virtual void did_finish_launching()
    {
        std::cout << "Did finish from C++!\n";
        UIRect window_frame = {
            .x = 0,
            .y = 0,
            .width = 1000,
            .height = 300};
        UI::Window *window = new UI::Window(window_frame);
        window->set_title("cereal");

        MyViewController *view_controller = new MyViewController();
        window->set_view_controller(view_controller);
    }
};

int main()
{
    UI::Application::main(new MyDelegate());
}