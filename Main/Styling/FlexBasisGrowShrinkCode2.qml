import QtQuick

import Flexbox

TestBox0 {
    Flexbox.width: 200
    Flexbox.height: 200
    Flexbox.padding: 10

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.flexGrow: 0.25
    }

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.flexGrow: 0.75
    }
}
