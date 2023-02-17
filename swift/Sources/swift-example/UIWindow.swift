import PanosUI

extension UIWindow {
    var title: String {
        get {
            return self.title
        }
        set {
            UIWindowSetTitle(self, newValue)
        }
    }

    var controller : UIWindowController {
        get {
            return self.controller
        }

        set {
            self.pointee.controller = newValue.backing
        }
    }

    var mainView: UIViewProtocol {
        get {
            return UIView(backing: self.pointee.mainView!)
        }
    }

    init(backing: UIWindow) {
        self = backing
    }

    init(frame: UIRect) {
        self = UIWindowCreate(frame)
    }

    func show() {
        UIWindowShow(self)
    }
}