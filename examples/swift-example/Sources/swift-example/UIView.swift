import PanosUI

extension UIView {
    init(backing: PanosUI.UIView) {
        self = backing
    }

    init(frame: UIRect) {
        self = UIViewCreate(frame, frame)
    }

    func addSubview(_ subview: UIView) {
        UIViewAddSubview(self, subview)
    }

    var frame: UIRect {
        get {
            return UIViewGetFrame(self)
        }
        set {
            UIViewSetFrame(self, newValue)
        }
    }
    var bounds: UIRect {
        get {
            return UIViewGetBounds(self)
        }
        set {
            UIViewSetBounds(self, newValue)
        }
    }
    var backgroundColor: UIColor {
        get {
            return UIViewGetBackgroundColor(self)
        }
        set {
            UIViewSetBackgroundColor(self, newValue)
        }
    }
    var cornerRadius: Float {
        get {
            return UIViewGetCornerRadius(self)
        }
        set {
            UIViewSetCornerRadius(self, newValue)
        }
    }
    var borderColor: UIColor {
        get {
            return UIViewGetBorderColor(self)
        }
        set {
            UIViewSetBorderColor(self, newValue)
        }
    }
    var borderWidth: Float {
        get {
            return UIViewGetBorderWidth(self)
        }
        set {
            UIViewSetBorderWidth(self, newValue)
        }
    }

    var shadowOffset: UIPoint {
        get {
            return UIViewGetShadowOffset(self)
        }
        set {
            UIViewSetShadowOffset(self, newValue)
        }
    }
    var shadowColor: UIColor {
        get {
            return UIViewGetShadowColor(self)
        }
        set {
            UIViewSetShadowColor(self, newValue)
        }
    }
    var shadowRadius: Float {
        get {
            return UIViewGetShadowRadius(self)
        }
        set {
            UIViewSetShadowRadius(self, newValue)
        }
    }
}