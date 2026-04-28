import QtQuick

import QtQuick.Controls
import QtQuick.Controls.Material

TextField {
    id: root

    property bool isEmphasisError: false

    Material.containerStyle: Material.Outlined

    onIsEmphasisErrorChanged: {
        if(isEmphasisError)
            focus = true
    }

    onTextChanged: {
        isEmphasisError = false
    }

    states: [
        State {
            name: "error"
            when: isEmphasisError
            PropertyChanges {
                target: root
                Material.accent: Material.Red
                Material.background: Material.Red
                Material.foreground: Material.Red
                focus: true
            }
        }

    ]
}
