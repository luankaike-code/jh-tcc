import QtQuick

import QtQuick.Controls
import QtQuick.Controls.Material

Image {
    id: root

    required property string activedSource
    required property string desactivedSource
    property bool checked: true

    signal actived
    signal desactived

    Component.onCompleted: {
        text = checked? activedText : desactivedText
    }

    source: root.checked? activedSource : desactivedSource
    width: 100
    height: 100

    sourceSize.width: width
    sourceSize.height: height

    MouseArea {
        anchors.fill: root
        onClicked: {
            checked = !checked
        }
    }
}
