import PanosUI

class UIResponder {
    var next: UIResponder?

    func leftMouseDown(event: UIEvent) {
        self.next?.leftMouseDown(event: event)
    }
    func leftMouseUp(event: UIEvent) {
        self.next?.leftMouseUp(event: event)
    }

    func rightMouseDown(event: UIEvent) {
        self.next?.rightMouseDown(event: event)
    }
    func rightMouseUp(event: UIEvent) {
        self.next?.rightMouseUp(event: event)
    }

    func mouseMove(event: UIEvent) {
        self.next?.mouseMove(event: event)
    }

    func mouseScroll(event: UIEvent) {
        self.next?.mouseScroll(event: event)
    }
}