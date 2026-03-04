import QtQuick

import Flexbox

TestBox0 {
    Flexbox.width: 200
    Flexbox.height: 250
    Flexbox.padding: 10
    Flexbox.alignContent: Flexbox.FlexStart
    Flexbox.flexWrap: Flexbox.Wrap

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
