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

extension UIView {
    var backgroundColor: UIColor {
        get {
            return UIViewGetBackgroundColor(self)
        }
        set {
            UIViewSetBackgroundColor(self, newValue)
        }
    }

    init(backing: PanosUI.UIView) {
        self = backing
    }

    init(frame: UIRect) {
        self = UIViewCreate(frame, frame)
    }

    func addSubview(subview: UIView) {
        UIViewAddSubview(self, subview)
    }
}

extension UIWindow {
    var title: String {
        get {
            return self.title
        }
        set {
            UIWindowSetTitle(self, newValue)
        }
    }

    init(backing: UIWindow) {
        self = backing
    }

    init(frame: UIRect) {
        self = UIWindowCreate(frame)
    }

    func show() {
        UIWindowShow(self)
    }
}

extension UIColor {
    init(r: Int32, g: Int32, b: Int32, a: Int32) {
        self.init()
        self.r = r
        self.g = g
        self.b = b
        self.a = a
    }
}

extension UIRect {
    init(x: Float, y: Float, width: Float, height: Float) {
        self.init()
        self.origin.x = x
        self.origin.y = y
        self.size.width = width
        self.size.height = height
    }
}

class UIWindowController {
    var backing: PanosUI.UIWindowController

    init() {
        self.backing = UIWindowControllerCreate()
        self.backing.pointee._self = UnsafeMutableRawPointer(Unmanaged.passUnretained(self).toOpaque())
        self.backing.pointee.windowDidLoad = { (this, window) in
            let controller = Unmanaged<UIWindowController>.fromOpaque(this!).takeUnretainedValue()
            controller.windowDidLoad(window: window)            
        }
    }

    func windowDidLoad(window: UIWindow?) {

    }
}

class MyWindowController : UIWindowController {
    override func windowDidLoad(window: UIWindow?) {
        let mainView = UIView(backing: window!.pointee.mainView!)
        var myView = UIView(frame: UIRect(x: 10, y: 10, width: 50, height: 50))
        
        myView.backgroundColor = UIColor(r: 0, g: 0, b: 0, a: 255)
        mainView.addSubview(subview: myView)

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

        UILayerAddAnimation(myView.pointee.layer, myAnim)
    }
}

struct MyDelegate: UIApplicationDelegate {
    let controller = MyWindowController()

    func didFinishLaunching() {
        print("Did finish from Swift!")

        var win = UIWindow(
            frame: UIRect(x: 0, y: 0, width: 750, height: 600)
        )

        win.pointee.controller = controller.backing

        win.show()
        win.title = "Hello Swift!"
    }
}

@main
public struct swift_example {
    public private(set) var text = "Hello, World!"

    public static func main() {
        Application.main(delegate: MyDelegate())
    }
}


