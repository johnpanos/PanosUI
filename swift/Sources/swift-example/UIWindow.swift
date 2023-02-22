import PanosUI

protocol UIWindowProtocol: AnyObject {
    var backing: PanosUI.UIWindow? { get }

    var title : String { get set }
    var controller : UIWindowController? { get set }
    var mainView: UIViewProtocol { get set }
}

extension UIWindowProtocol {
    var title: String {
        get {
            return String(cString: self.backing!.pointee.title)
        }
        set {
            UIWindowSetTitle(self.backing, newValue)
        }
    }

    func show() {
        UIWindowShow(self.backing)
    }
}

class UIWindow : UIWindowProtocol {
    var controller: UIWindowController? {
        get {

        }

        set {
            newValue.window
        }
    }

    fileprivate var _mainView: UIViewProtocol?
    var mainView: UIViewProtocol {
        get {
            return self._mainView!
        }

        set {
            self._mainView = newValue
        }
    }

    var backing: PanosUI.UIWindow?

    init(backing: PanosUI.UIWindow) {
        self.backing = backing
        self._mainView = self.backing?.pointee.mainView.toSwift()
    }

    init(frame: UIRect) {
        self.backing = UIWindowCreate(frame)
        self._mainView = self.backing?.pointee.mainView.toSwift()
    }
}