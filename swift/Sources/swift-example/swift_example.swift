import PanosUI

class BlackSquareView : UIView {
    override init(frame: UIRect) {
        super.init(frame: frame)
        self.backgroundColor = UIColor(r: 0, g: 0, b: 0, a: 255)
        self.shadowOffset = UIPoint(x: 0, y: 0)
        self.shadowRadius = 12
        self.shadowColor = UIColor(r: 255, g: 0, b: 0, a: 200)
        self.cornerRadius = 24
    }
}

class MyWindowController : UIWindowController {
    var myView: UIView = BlackSquareView(
            frame: UIRect(x: 0, y: 0, w: 0, h: 0)
        )

    override func windowDidLoad(window: UIWindow) {      
        self.myView.frame = window.mainView.frame.inset(dx: 100, dy: 100)
        window.mainView.addSubview(self.myView)
    }
}

struct MyDelegate: UIApplicationDelegate {
    let windowController: MyWindowController = MyWindowController()
    var window: UIWindow! {
        didSet {
            window.controller = windowController
            window.show()
            window.title = "Swift Window"
        }
    }

    mutating func didFinishLaunching() {
        self.window = UIWindow(frame: UIRect(x: 0, y: 0, w: 750, h: 600))
    }
}

@main
public struct swift_example {
    public static func main() {
        UIApplication.main(delegate: MyDelegate())
    }
}