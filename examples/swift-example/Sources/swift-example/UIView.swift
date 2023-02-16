import PanosUI

protocol EventResponder {
    var next: UIEventResponder? { get }

    mutating func leftMouseDown(event: UIEvent)
    mutating func leftMouseUp(event: UIEvent)

    mutating func rightMouseDown(event: UIEvent)
    mutating func rightMouseUp(event: UIEvent)

    mutating func mouseMove(event: UIEvent)

    mutating func mouseScroll(event: UIEvent)
}

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

// extension UIEventResponder : EventResponder {
//     var next: UIEventResponder? {
//         get {
//             return self.next
//         }
//         set {
//             self.pointee.next = newValue
//         }
//     }

//     mutating func leftMouseDown(event: UIEvent) {
//         self.next?.leftMouseDown(event: event)
//     }

//     mutating func leftMouseUp(event: UIEvent) {
//         self.next?.leftMouseUp(event: event)
//     }

//     mutating func rightMouseDown(event: UIEvent) {
//         self.next?.rightMouseDown(event: event)
//     }

//     mutating func rightMouseUp(event: UIEvent) {
//         self.next?.rightMouseUp(event: event)
//     }

//     mutating func mouseMove(event: UIEvent) {
//         self.next?.mouseMove(event: event)
//     }

//     mutating func mouseScroll(event: UIEvent) {
//         self.next?.mouseScroll(event: event)
//     }
// }

// extension UIView : EventResponder {
//     var next: EventResponder? {
//         get {
//             return self.pointee.responder.next
//         }
//     }

//     mutating func leftMouseDown(event: UIEvent) {
        
//     }

//     mutating func leftMouseUp(event: UIEvent) {
        
//     }

//     mutating func rightMouseDown(event: UIEvent) {
        
//     }

//     mutating func rightMouseUp(event: UIEvent) {
        
//     }

//     mutating func mouseMove(event: UIEvent) {
        
//     }

//     mutating func mouseScroll(event: UIEvent) {
        
//     }
// }