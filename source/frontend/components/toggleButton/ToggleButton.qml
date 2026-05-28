import QtQuick

import "../imageButton"

ImageButton {
    id: root

    required property string activedSource
    required property string desactivedSource
    property bool checked: true

    signal checkedUpdate()

    source: checked? activedSource : desactivedSource

    sourceSize.width: width
    sourceSize.height: height

    onCheckedChanged: {
        checked = checked
    }

    onClicked: {
        checked = !checked
    }
}
