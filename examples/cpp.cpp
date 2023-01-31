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
    }
};

class MyDelegate : public UI::ApplicationDelegate
{
    virtual void did_finish_launching()
    {
        std::cout << "Did finish from C++!\n";
        UI::Window *window = new UI::Window();
        window->set_title("Example");

        MyViewController *viewController = new MyViewController();
        window->set_view_controller(viewController);
    }
};

int main()
{
    UI::Application::main(new MyDelegate());
}