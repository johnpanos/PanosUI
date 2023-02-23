#include "ui/UIApplication.hpp"
#include "ui/UIView.hpp"
#include "ui/UIWindow.hpp"
#include <memory>

class BlackSquareView : public UI::View
{
  public:
	BlackSquareView(UIRect frame) : UI::View(frame, frame)
	{
		this->set_background_color(UIColorCreateRGBA(0, 0, 0, 255));
		this->set_shadow_offset(UIPointCreate(0, 0));
		this->set_shadow_radius(12);
		this->set_shadow_color(UIColorCreateRGBA(255, 0, 0, 200));
		this->set_corner_radius(24);
	}
};

class MyWindowController : public UI::WindowController
{
	std::shared_ptr<UI::View> my_view = std::make_unique<BlackSquareView>(UIRectCreate(0, 0, 0, 0));

	virtual void window_did_load()
	{
		this->my_view->set_frame(UIRectInset(this->window->get_main_view()->get_frame(), 100, 100));
		this->window->get_main_view()->add_subview(this->my_view.get());
	}
};

class MyDelegate : public UI::ApplicationDelegate
{
	MyWindowController *window_controller = new MyWindowController();
	std::unique_ptr<UI::Window> window;

	virtual void did_finish_launching()
	{
		this->window = std::make_unique<UI::Window>(UIRectCreate(0, 0, 750, 600));

		window->set_controller(window_controller);
		window->show();
		window->set_title("C++ Window");
	}
};

int main()
{
	UI::Application::main(new MyDelegate());
}