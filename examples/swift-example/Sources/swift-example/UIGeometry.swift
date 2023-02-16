import PanosUI

extension UIRect {
    init(x: Float, y: Float, width: Float, height: Float) {
        self.init()
        self.origin.x = x
        self.origin.y = y
        self.size.width = width
        self.size.height = height
    }

    var mixX: Float {
        get {
            return UIRectGetMinX(self)
        }
    }

    
    var minY: Float {
        get {
            return UIRectGetMinY(self)
        }
    }
    
    var maxX: Float {
        get {
            return UIRectGetMaxX(self)
        }
    }
    
    var maxY: Float {
        get {
            return UIRectGetMaxY(self)
        }
    }
    
    var midX: Float {
        get {
            return UIRectGetMidX(self)
        }
    }
    
    var midY: Float {
        get {
            return UIRectGetMidY(self)
        }
    }

    func inset(dx: Float, dy: Float) -> UIRect {
        return UIRectInset(self, dx, dy)
    }

    func outset(dx: Float, dy: Float) -> UIRect {
        return UIRectOutset(self, dx, dy)
    }

    func pointInRect(p: UIPoint) -> Bool {
        return UIPointInRect(p, self)
    }
}

extension UIPoint {
    init(x: Float, y: Float) {
        self = UIPointCreate(x, y)
    }

    func offset(dx: Float, dy: Float) -> UIPoint {
        return UIPointOffset(self, dx, dy)
    }
}