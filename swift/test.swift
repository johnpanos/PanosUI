// class UIView {
//     var _backingView: UnsafeMutablePointer<_UIView>

//     var frame: UIRect {
//         get {
//             return _backingView.pointee.frame
//         }
//         set(newFrame) {
//             _backingView.pointee.frame = newFrame
//         }
//     }
//     var bounds: UIRect {
//         get {
//             return _backingView.pointee.bounds
//         }
//         set(newBounds) {
//             _backingView.pointee.bounds = newBounds
//         }
//     }

//     init(frame: UIRect, bounds: UIRect) {
//         self._backingView = UIViewCreate(frame, bounds)
//     }

//     deinit {
//         print("deinit")
//         UIViewDestroy(_backingView)
//     }

//     func addSubview(child: UIView) {
//         UIViewAddSubview(_backingView, child._backingView);
//     }
// }

struct Application {
    private static var DELEGATE: UIApplicationDelegate?
    static func main(delegate: UIApplicationDelegate) {
        Application.DELEGATE = delegate
        var cDelegate: _UIApplicationDelegate = _UIApplicationDelegate(didFinishLaunching: { app in
            Application.DELEGATE!.didFinish()
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
    }
}

Application.main(delegate: MyDelegate())