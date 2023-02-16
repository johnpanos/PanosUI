// import PanosUI
// import Foundation

// struct UIArray<T> : Collection {
//     var backing: PanosUI.Array

//     init(backing: PanosUI.Array) {
//         self.backing = backing
//     }

//     // Required nested types, that tell Swift what our collection contains
//     typealias Index = Int32
//     typealias Element = T

//     // The upper and lower bounds of the collection, used in iterations
//     var startIndex: Index { return 0 }
//     var endIndex: Index { return Int32(ArrayGetCapacity(backing)) }

//     // Required subscript, based on a dictionary index
//     subscript(index: Index) -> Iterator.Element {
//         get { return ArrayGetValueAtIndex(self.backing, index) as! T }
//     }

//     // Method that returns the next index when iterating
//     func index(after i: Index) -> Index {
//         return i
//     }
// }