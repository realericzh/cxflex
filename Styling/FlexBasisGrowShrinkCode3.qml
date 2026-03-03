import QtQuick

import Flexbox

TestBox0 {
    Flexbox.width: 200
    Flexbox.height: 200
    Flexbox.padding: 10

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.flexShrink: 5
        Flexbox.height: 150
    }

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.flexShrink: 10
        Flexbox.height: 150
    }
}
