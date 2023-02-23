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

class BlackSquareWindowController : UIWindowController {
    var myView: UIView = BlackSquareView(
            frame: UIRectCreate(0, 0, 0, 0)
        )

    override func windowDidLoad(window: UIWindow) {      
        self.myView.frame = window.mainView.frame.inset(dx: 100, dy: 100)
        window.mainView.addSubview(self.myView)
    }
}

struct MyDelegate: UIApplicationDelegate {
    let blackSquare: BlackSquareWindowController = BlackSquareWindowController()
    var window: UIWindow! {
        didSet {
            window.controller = blackSquare
            window.show()
            window.title = "Black Square!"
        }
    }
    var window2: UIWindow! {
        didSet {
            window2.show()
            window2.title = "idk"
            window2.mainView.backgroundColor = UIColor(r: 255, g: 0, b: 0, a: 255)
        }
    }

    mutating func didFinishLaunching() {
        self.window = UIWindow(frame: UIRect(x: 0, y: 0, width: 750, height: 600))
        self.window2 = UIWindow(frame: UIRect(x: 0, y: 0, width: 250, height: 250))
    }
}

@main
public struct swift_example {
    public static func main() {
        UIApplication.main(delegate: MyDelegate())
    }
}