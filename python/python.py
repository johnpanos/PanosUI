from panosui import UIApplication, UIApplicationDelegate, UIWindow
from panosui_c import UIRect, UIPoint, UISize

class MyDelegate(UIApplicationDelegate):
    def did_finish_launching(self):
        print("Did finish launching from Python!")
        rect = UIRect(UIPoint(0, 0), UISize(500, 500))

        win = UIWindow(rect)
        win.show()
        win.title = "Python Window"

if __name__ == "__main__":
    delegate = MyDelegate()
    UIApplication.main(delegate)