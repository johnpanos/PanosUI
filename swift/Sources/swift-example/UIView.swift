import PanosUI

protocol UIViewProtocol: AnyObject {
    var backing: PanosUI.UIView { get }
}

extension UIViewProtocol {
    func addSubview(_ subview: UIViewProtocol) {
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
    var backgroundColor: UIColor {
        get {
            return UIViewGetBackgroundColor(self.backing)
        }
        set {
            UIViewSetBackgroundColor(self.backing, newValue)
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
    var borderColor: UIColor {
        get {
            return UIViewGetBorderColor(self.backing)
        }
        set {
            UIViewSetBorderColor(self.backing, newValue)
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
    var shadowColor: UIColor {
        get {
            return UIViewGetShadowColor(self.backing)
        }
        set {
            UIViewSetShadowColor(self.backing, newValue)
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

// extension PanosUI.UIView : UIViewProtocol, CustomStringConvertible {
//     public var description: String { return "UIView: \(self.frame) \(self.bounds)" }

//     var backing: PanosUI.UIView {
//         get {
//             return self
//         }
//     }

//     init(backing: PanosUI.UIView) {
//         self = backing
//     }

//     init(frame: UIRect) {
//         self = UIViewCreate(frame, frame)
//     }
// }

class UIView : UIViewProtocol, UIEventResponderProtocol {
    var backing: PanosUI.UIView

    init(backing: PanosUI.UIView) {
        self.backing = backing
    }

    init(frame: UIRect) {
        self.backing = UIViewCreate(frame, frame)
        self.backing.pointee.responder.pointee._self = UnsafeMutableRawPointer(Unmanaged.passUnretained(self).toOpaque())
        self.backing.pointee.responder.pointee.leftMouseDown = { (this: PanosUI.UIEventResponder?, event: UIEvent) in
            let view: UIView = Unmanaged<UIView>.fromOpaque(this!.pointee._self!).takeUnretainedValue()
            view.leftMouseDown(event: event)            
        }
    }

    func leftMouseDown(event: UIEvent) {
        
    }

    func leftMouseUp(event: UIEvent) {
        
    }

    func rightMouseDown(event: UIEvent) {
        
    }

    func rightMouseUp(event: UIEvent) {
        
    }

    func mouseMove(event: UIEvent) {
        
    }

    func mouseScroll(event: UIEvent) {
        
    }
}

class UILabel : UIViewProtocol {
    var backing: PanosUI.UIView

    var label: PanosUI.UILabel

    init(frame: UIRect) {
        self.label = UILabelCreate(frame)
        self.backing = unsafeBitCast(self.label, to: UnsafeMutablePointer<_UIView>.self)
    }

    var contents: String {
        get {
            return String(cString: UILabelGetContents(self.label))
        }
        set {
            UILabelSetContents(self.label, newValue)
        }
    }

    var fontSize: Float {
        get {
            return UILabelGetFontSize(self.label)
        }
        set {
            UILabelSetFontSize(self.label, newValue)
        }
    }

    var fontColor: UIColor {
        get {
            return UILabelGetFontColor(self.label)
        }
        set {
            UILabelSetFontColor(self.label, newValue)
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