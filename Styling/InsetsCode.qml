import QtQuick

import Flexbox

TestBox0 {
    Flexbox.width: 200
    Flexbox.height: 200

    TestBox1 {
        Flexbox.height: 50
        Flexbox.width: 50
        Flexbox.top: 50
        Flexbox.left: 50
    }
}
