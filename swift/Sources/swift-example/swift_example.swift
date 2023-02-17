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

    override func leftMouseDown(event: UIEvent) {
        var start: Float = self.frame.size.width
        var end: Float = 200.0

        var myAnim: UIAnimation = UIAnimation()
        myAnim.finished = 0
        myAnim.forKey = kUILayerKeyBoundsWidth
        myAnim.timingFunction = UIAnimationTimingFunctionEaseInOutQuart
        myAnim.startValue = .init(&start)
        myAnim.endValue = .init(&end)
        myAnim.startTime = UIAnimationGetCurrentTime()
        myAnim.endTime = UIAnimationGetCurrentTime() + 2500
        myAnim._valueSize = MemoryLayout<Float>.size
        myAnim.duration = 2500

        UILayerAddAnimation(self.backing.pointee.layer, myAnim)

        start = self.frame.size.height
        myAnim.forKey = kUILayerKeyBoundsHeight
        UILayerAddAnimation(self.backing.pointee.layer, myAnim)

        start = self.cornerRadius
        myAnim.forKey = kUILayerKeyCornerRadius
        UILayerAddAnimation(self.backing.pointee.layer, myAnim)
    }
}

class BlackSquareWindowController : UIWindowController {
    var myView: UIView?

    override func windowDidLoad(window: UIWindow) {
        self.myView = BlackSquareView(
            frame: window.mainView.frame.inset(dx: 50, dy: 50)
        )
        
        window.mainView.addSubview(myView!)
    }
}

class RedCircleWindowController : UIWindowController {
    var myView: UIView! {
        didSet {
            myView.backgroundColor = UIColor(r: 255, g: 0, b: 0, a: 255)
            myView.shadowOffset = UIPoint(x: 2, y: 2)
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
        // self.redCircleWindow = UIWindow(frame: UIRect(x: 0, y: 0, width: 600, height: 600))
    }
}

@main
public struct swift_example {
    public static func main() {
        UIApplication.main(delegate: MyDelegate())
    }
}