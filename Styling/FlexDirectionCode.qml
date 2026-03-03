import QtQuick

import Flexbox

TestBox0 {
    Flexbox.width: 200
    Flexbox.height: 200
    Flexbox.padding: 10
    Flexbox.flexDirection: Flexbox.Column

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.height: 50
        Flexbox.width: 50
    }

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.height: 50
        Flexbox.width: 50
    }
}
