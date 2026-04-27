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

    source: root.checked? activedSource : desactivedSource

    sourceSize.width: width
    sourceSize.height: height

    MouseArea {
        anchors.fill: root
        onClicked: {
            checked = !checked
        }
    }
}
