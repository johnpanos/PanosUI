import PanosUI

class BlackSquareWindowController : UIWindowController {
    var myView: UIView! {
        didSet {
            myView.backgroundColor = UIColor(r: 0, g: 0, b: 0, a: 255)
            myView.shadowOffset = UIPointCreate(2, 2)
            myView.shadowRadius = 4.0
            myView.shadowColor = UIColor(r: 255, g: 0, b: 0, a: 100)
            myView.cornerRadius = 10.0
        }
    }

    override func windowDidLoad(window: UIWindow) {
        self.myView = UIView(
            frame: window.mainView.frame.inset(dx: 50, dy: 50)
        )

        var myLabel: UILabel = UILabel(frame: window.mainView.frame.inset(dx: 100, dy: 100))

        myLabel.fontSize = 20
        myLabel.backgroundColor = UIColor(r: 255, g: 255, b: 0, a: 255)
        
        window.mainView.addSubview(myView)
        window.mainView.addSubview(myLabel)
    }
}

class RedCircleWindowController : UIWindowController {
    var myView: UIView! {
        didSet {
            myView.backgroundColor = UIColor(r: 255, g: 0, b: 0, a: 255)
            myView.shadowOffset = UIPointCreate(2, 2)
            myView.cornerRadius = 1000.0
        }
    }

    override func windowDidLoad(window: UIWindow) {
        self.myView = UIView(
            frame: window.mainView.frame.inset(dx: 50, dy: 50)
        )

        window.mainView.addSubview(myView)
    }
}

struct MyDelegate: UIApplicationDelegate {
    let blackSquare: BlackSquareWindowController = BlackSquareWindowController()
    var blackSquareWindow: UIWindow! {
        didSet {
            blackSquareWindow.controller = blackSquare
            blackSquareWindow.show()
            blackSquareWindow.title = "Black Square!"
        }
    }

    let redCircle: RedCircleWindowController = RedCircleWindowController()
    var redCircleWindow: UIWindow! {
        didSet {
            redCircleWindow.controller = redCircle
            redCircleWindow.show()
            redCircleWindow.title = "Red Circle!"
        }
    }

    mutating func didFinishLaunching() {
        print("Did finish from Swift!")
        self.blackSquareWindow = UIWindow(frame: UIRect(x: 0, y: 0, width: 750, height: 600))
        self.redCircleWindow = UIWindow(frame: UIRect(x: 0, y: 0, width: 600, height: 600))
    }
}

@main
public struct swift_example {
    public static func main() {
        UIApplication.main(delegate: MyDelegate())
    }
}