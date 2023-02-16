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

        let rect = UIRectCreate(0, 0, 750, 600)
        let win = UIWindowCreate(rect)

        let windowController = UIWindowControllerCreate()
        windowController!.pointee.windowDidLoad = { window in
            let myFrame = UIRectCreate(10, 10, 50, 50)
            let myView = UIViewCreate(myFrame, myFrame)
            
            UIViewSetBackgroundColor(myView, UIColorCreateRGBA(0, 0, 0, 255))
            UIViewAddSubview(window!.pointee.mainView, myView)

            var start: Float = 100.0
            var end: Float = 500.0

            var myAnim: UIAnimation = UIAnimation()
            myAnim.finished = 0
            myAnim.forKey = kUILayerKeyPositionX
            myAnim.timingFunction = UIAnimationTimingFunctionEaseInOutCubic
            myAnim.startValue = .init(&start)
            myAnim.endValue = .init(&end)
            myAnim.startTime = UIAnimationGetCurrentTime()
            myAnim.endTime = UIAnimationGetCurrentTime() + 2500
            myAnim._valueSize = MemoryLayout<Float>.size
            myAnim.duration = 2500

            UILayerAddAnimation(myView!.pointee.layer, myAnim)
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


