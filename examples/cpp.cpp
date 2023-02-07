#include <stdio.h>
#include <iostream>
#include "ui/UIApplication.hpp"
#include "ui/UIWindow.hpp"

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
        window->show();
        window->set_title("cereal");

        UI::Window *window2 = new UI::Window(window_frame);
        window2->show();
        window2->set_title("cereal2");
    }
};

int main()
{
    UI::Application::main(new MyDelegate());
}