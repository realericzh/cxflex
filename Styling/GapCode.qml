import QtQuick

import Flexbox

TestBox0 {
    Flexbox.width: 200
    Flexbox.height: 250
    Flexbox.padding: 10
    Flexbox.flexWrap: Flexbox.Wrap
    Flexbox.gap: 10

    TestBox1 {
        Flexbox.height: 50
        Flexbox.width: 50
    }

    TestBox1 {
        Flexbox.height: 50
        Flexbox.width: 50
    }

    TestBox1 {
        Flexbox.height: 50
        Flexbox.width: 50
    }

    TestBox1 {
        Flexbox.height: 50
        Flexbox.width: 50
    }
}
