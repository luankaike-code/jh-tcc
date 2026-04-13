import QtQuick 2.15

import QtQuick.Controls 6.11

TextField {
    id: root

    property bool isEmphasisError: false

    background: Rectangle {
        color: "white"
        border.color: root.isEmphasisError? "red" : "black"
        border.width: 1
    }
}
