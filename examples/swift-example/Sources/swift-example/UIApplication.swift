import PanosUI

struct UIApplication {
    private static var DELEGATE: UIApplicationDelegate?
    static func main(delegate: UIApplicationDelegate) {
        UIApplication.DELEGATE = delegate
        var cDelegate = _UIApplicationDelegate(didFinishLaunching: { app in
            UIApplication.DELEGATE!.didFinishLaunching()
        })
        withUnsafeMutablePointer(to: &cDelegate) { pp in
            UIApplicationMain(pp)    
        }
    }
}

protocol UIApplicationDelegate {
    mutating func didFinishLaunching()
}
