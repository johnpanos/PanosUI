import PanosUI

protocol UIEventResponderProtocol: AnyObject {
    func leftMouseDown(event: UIEvent)
    func leftMouseUp(event: UIEvent)

    func rightMouseDown(event: UIEvent)
    func rightMouseUp(event: UIEvent)

    func mouseMove(event: UIEvent)

    func mouseScroll(event: UIEvent)
}

// class UIResponder {
//     var backing: PanosUI.UIEventResponder

//     init() {
//         self.backing = UIEventResponderCreate()
//     }

//     func leftMouseDown(event: UIEvent) {

//     }
// }