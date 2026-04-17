import QtQuick 2.15

import QtQuick.Controls 6.5

TextField {
    id: root

    property bool isEmphasisError: false

    color: "black"
    placeholderTextColor: "gray"

    background: Rectangle {
        color: "white"
        border.color: root.isEmphasisError? "red" : "black"
        border.width: 1
    }
}
