import QtQuick

import Flexbox

TestBox0 {
    Flexbox.width: 200
    Flexbox.height: 200
    Flexbox.padding: 10

    TestBox1 {
        Flexbox.margin: 5
        Flexbox.padding: 20
        Flexbox.horizontalBorder: 20
        Flexbox.height: 50
    }

    TestBox1 {
        Flexbox.height: 50
    }
}
