import QtQuick

import Flexbox

TestBox0 {
    Flexbox.width: 200
    Flexbox.height: 250
    Flexbox.padding: 10

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.height: 25
    }

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.height: 100
        Flexbox.maximumHeight: 25
    }

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.height: 25
        Flexbox.minimumHeight: 50
    }

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.height: 25
        Flexbox.maximumWidth: 25
    }

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.height: 25
        Flexbox.width: 25
        Flexbox.minimumWidth: 50
    }
}
