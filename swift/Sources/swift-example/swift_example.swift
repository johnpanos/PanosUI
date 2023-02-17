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
    var myView: UIView!

    override func windowDidLoad(window: UIWindow) {
        self.myView = BlackSquareView(
            frame: window.mainView.frame.inset(dx: 100, dy: 100)
        )
        
        window.mainView.addSubview(myView)
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

    mutating func didFinishLaunching() {
        print("Did finish from Swift!")
        self.window = UIWindow(frame: UIRect(x: 0, y: 0, width: 750, height: 600))
    }
}

@main
public struct swift_example {
    public static func main() {
        UIApplication.main(delegate: MyDelegate())
    }
}