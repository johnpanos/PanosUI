import PanosUI

class UIWindowController {
    var backing: PanosUI.UIWindowController

    init() {
        self.backing = UIWindowControllerCreate()
        self.backing.pointee._self = UnsafeMutableRawPointer(Unmanaged.passUnretained(self).toOpaque())
        self.backing.pointee.windowDidLoad = { (this: UnsafeMutableRawPointer?, window: UIWindow?) in
            let controller: UIWindowController = Unmanaged<UIWindowController>.fromOpaque(this!).takeUnretainedValue()
            controller.windowDidLoad(window: window!)            
        }
    }

    func windowDidLoad(window: UIWindow) {

    }
}