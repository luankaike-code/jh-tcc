import QtQuick

import "../imageButton"

ImageButton {
    id: root

    QtObject {
        id: variables
        property bool checked: true
    }

    required property string activedSource
    required property string desactivedSource
    property bool checked: true

    signal checkedUpdate(bool is_checked)

    function emitCheckedUpdate() {
        checkedUpdate(variables.checked)
    }

    source: variables.checked? activedSource : desactivedSource

    sourceSize.width: width
    sourceSize.height: height

    onCheckedChanged: {
        if(variables.checked === checked)
            return

        variables.checked = checked
        emitCheckedUpdate()
    }

    onClicked: {
        variables.checked = !variables.checked
        emitCheckedUpdate()
    }
}
