import PanosUI

class UIView {
    internal var backing: OpaquePointer? {
        didSet {
            self._backgroundColor = UIColor(backing: UIViewGetBackgroundColor(self.backing))
            self._borderColor = UIColor(backing: UIViewGetBorderColor(self.backing))
            self._shadowColor = UIColor(backing: UIViewGetShadowColor(self.backing))
        }
    }

    internal init(backing: OpaquePointer) {
        self.backing = backing
    }

    init(frame: UIRect) {
        self.backing = UIViewCreate(frame, frame)
    }

    deinit {
        UIViewDestroy(self.backing)
    }

    func addSubview(_ subview: UIView) {
        UIViewAddSubview(self.backing, subview.backing)
    }

    var frame: UIRect {
        get {
            return UIViewGetFrame(self.backing)
        }
        set {
            UIViewSetFrame(self.backing, newValue)
        }
    }
    var bounds: UIRect {
        get {
            return UIViewGetBounds(self.backing)
        }
        set {
            UIViewSetBounds(self.backing, newValue)
        }
    }
    private var _backgroundColor: UIColor!
    var backgroundColor: UIColor {
        get {
            return self._backgroundColor
        }
        set {
            self._backgroundColor = newValue
            UIViewSetBackgroundColor(self.backing, self._backgroundColor.backing)
        }
    }
    var cornerRadius: Float {
        get {
            return UIViewGetCornerRadius(self.backing)
        }
        set {
            UIViewSetCornerRadius(self.backing, newValue)
        }
    }

    private var _borderColor: UIColor!
    var borderColor: UIColor {
        get {
            return self._borderColor
        }
        set {
            self._borderColor = newValue
            UIViewSetBorderColor(self.backing, self._borderColor.backing)
        }
    }
    var borderWidth: Float {
        get {
            return UIViewGetBorderWidth(self.backing)
        }
        set {
            UIViewSetBorderWidth(self.backing, newValue)
        }
    }

    var shadowOffset: UIPoint {
        get {
            return UIViewGetShadowOffset(self.backing)
        }
        set {
            UIViewSetShadowOffset(self.backing, newValue)
        }
    }
    private var _shadowColor: UIColor!
    var shadowColor: UIColor {
        get {
            return self._shadowColor
        }
        set {
            self._shadowColor = newValue
            UIViewSetShadowColor(self.backing, self._shadowColor.backing)
        }
    }
    var shadowRadius: Float {
        get {
            return UIViewGetShadowRadius(self.backing)
        }
        set {
            UIViewSetShadowRadius(self.backing, newValue)
        }
    }
}

extension UIView: CustomDebugStringConvertible {
    var debugDescription: String {
        get {
            return "frame(\(self.frame)) bounds:(\(self.bounds))"
        }
    }
}