from panosui_c import UIApplication, UIApplicationMain, UIApplicationDelegate, UIColorCreateRGBA, UIRect, UIPoint, UISize
from panosui import UIWindow


def did_finish_launching(a):
    print("Did finish launching from Python")
    rect = UIRect(UIPoint(0, 0), UISize(500, 500))

    win = UIWindow(rect)
    win.show()
    win.title = "Python Window"

if __name__ == "__main__":
    delegate = UIApplicationDelegate(UIApplicationDelegate._fields_[0][1](did_finish_launching))
    UIApplicationMain(delegate)