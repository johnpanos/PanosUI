#include <stdio.h>
#include <iostream>
#include "ui/UIApplication.hpp"
#include "ui/UIWindow.hpp"

class MyWindowController : public UI::WindowController
{
    virtual void on_window_load()
    {
        std::cout << "Window did load from C++!\n";
    }
};

class MyDelegate : public UI::ApplicationDelegate
{
    virtual void did_finish_launching()
    {
        std::cout << "Did finish from C++!\n";
        UIRect window_frame;
        window_frame.x = 0;
        window_frame.y = 0;
        window_frame.width = 1000;
        window_frame.height = 300;

        UI::Window *window = new UI::Window(window_frame);
        window->set_title("cereal");

        MyWindowController *my_window_controller = new MyWindowController();
        window->set_window_controller(my_window_controller);
    }
};

int main()
{
    UI::Application::main(new MyDelegate());
}