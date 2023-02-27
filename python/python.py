from panosui import UIApplication, UIApplicationDelegate, UIWindow, UIView
from panosui_c import UIRect, UIPoint, UISize, UIRectInset, UIColorCreateRGBA

class MyDelegate(UIApplicationDelegate):
    def did_finish_launching(self):
        print("Did finish launching from Python!")
        rect = UIRect(UIPoint(0, 0), UISize(1000, 500))

        view = UIView(frame=UIRectInset(rect, 32, 32))   
        view.backgroundColor = UIColorCreateRGBA(0, 0, 0, 255)     

        win = UIWindow(rect)
        win.mainView.addSubview(view)

        win.show()
        win.title = "Python Window"

if __name__ == "__main__":
    delegate = MyDelegate()
    UIApplication.main(delegate)