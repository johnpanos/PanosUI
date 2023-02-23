import PanosUI

class UIColor {
    internal var backing: OpaquePointer?

    internal init(backing: OpaquePointer) {
        self.backing = backing
    }

    init(r: Int32, g: Int32, b: Int32, a: Int32) {
        self.backing = UIColorCreateRGBA(r, g, b, a)
    }

    deinit {
        print("Destroying UIColor")
        UIColorDestroy(self.backing)
    }
}