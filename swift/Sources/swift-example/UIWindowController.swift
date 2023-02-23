import PanosUI

class UIWindowController {
    var backing: UnsafeMutablePointer<PanosUI.UIWindowController>
    var window: UIWindow?

    init() {
        self.backing = UIWindowControllerCreate()
        self.backing.pointee._self = UnsafeMutableRawPointer(Unmanaged.passUnretained(self).toOpaque())
        self.backing.pointee.windowDidLoad = { (this: UnsafeMutableRawPointer?, window: OpaquePointer?) in
            let controller: UIWindowController = Unmanaged<UIWindowController>.fromOpaque(this!).takeUnretainedValue()
            controller.windowDidLoad(window: controller.window!)            
        }
    }

    func windowDidLoad(window: UIWindow) {

    }
}