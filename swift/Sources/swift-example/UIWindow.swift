import PanosUI

class UIWindow {
    private var _controller: UIWindowController?

    var controller: UIWindowController? {
        get {
            return self._controller
        }

        set {
            newValue?.window = self
            self._controller = newValue
            UIWindowSetController(self.backing, self._controller?.backing)
        }
    }

    internal var backing: OpaquePointer? {
        didSet {
            self._mainView = UIView(backing: UIWindowGetMainView(self.backing))
        }
    }

    internal var _mainView: UIView!
    var mainView: UIView {
        get {
            return self._mainView
        }
    }

    var title: String {
        get {
            return ""
        }
        set {
            UIWindowSetTitle(self.backing, newValue)
        }
    }

    init(backing: OpaquePointer?) {
        defer {
            self.backing = backing
        }
    }

    init(frame: UIRect) {
        defer {
            self.backing = UIWindowCreate(frame)
        }
    }

    deinit {
        print("WINDOW DESTROY")
    }

    func show() {
        UIWindowShow(self.backing)
    }
}