import QtQuick

import Flexbox

TestBox0 {
    Flexbox.width: 200
    Flexbox.height: 200
    Flexbox.padding: 10

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.height: 50
        Flexbox.top: 20
        Flexbox.position: Flexbox.Relative
    }
}
