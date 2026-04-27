import QtQuick

import "../imageButton"

ImageButton {
    id: root

    required property string activedSource
    required property string desactivedSource
    property bool checked: true

    signal actived
    signal desactived

    source: root.checked? activedSource : desactivedSource

    sourceSize.width: width
    sourceSize.height: height

    onClicked: {
        checked = !checked
    }
}
