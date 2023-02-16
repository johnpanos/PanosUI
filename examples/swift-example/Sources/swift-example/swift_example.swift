import PanosUI

struct Application {
    private static var DELEGATE: UIApplicationDelegate?
    static func main(delegate: UIApplicationDelegate) {
        Application.DELEGATE = delegate
        var cDelegate = _UIApplicationDelegate(didFinishLaunching: { app in
            Application.DELEGATE!.didFinishLaunching()
        })
        withUnsafeMutablePointer(to: &cDelegate) { pp in
            UIApplicationMain(pp)    
        }
    }
}

protocol UIApplicationDelegate {
    func didFinishLaunching()
}



struct MyDelegate: UIApplicationDelegate {
    func didFinishLaunching() {
        print("Did finish from Swift!")

        let rect = UIRectCreate(0, 0, 100, 100)
        let win = UIWindowCreate(rect)

        let windowController = UIWindowControllerCreate()
        windowController!.pointee.windowDidLoad = { window in
            let myFrame = UIRectCreate(10, 10, 50, 50)
            let myView = UIViewCreate(myFrame, myFrame)
            
            UIViewSetBackgroundColor(myView, UIColorCreateRGBA(0, 0, 0, 255))
            UIViewAddSubview(window!.pointee.mainView, myView)
        }

        win!.pointee.controller = windowController

        UIWindowShow(win)
        UIWindowSetTitle(win, "Hello World")
    }
}

@main
public struct swift_example {
    public private(set) var text = "Hello, World!"

    public static func main() {
        Application.main(delegate: MyDelegate())
    }
}


