import QtQuick

import QtQuick.Controls
import QtQuick.Controls.Material

TextField {
    id: root

    property bool isEmphasisError: false
    onIsEmphasisErrorChanged: {
        if(isEmphasisError)
            focus = true
    }
    onTextChanged: {
        isEmphasisError = false
    }

    Material.accent: isEmphasisError? Material.Red : Material.Blue
    Material.background: isEmphasisError? Material.Red : Material.Blue
    Material.foreground: isEmphasisError? Material.Red : Material.BlueGrey

    Material.containerStyle: Material.Outlined
}
