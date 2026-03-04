import QtQuick

import Flexbox

TestBox0 {
    Flexbox.width: 200
    Flexbox.height: 250
    Flexbox.padding: 10
    Flexbox.alignContent: Flexbox.FlexStart

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.height: 50
        Flexbox.width: 50
        Flexbox.alignSelf: Flexbox.Center
    }

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.height: 50
        Flexbox.width: 50
    }
}
