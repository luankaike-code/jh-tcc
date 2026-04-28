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

    Material.accent: isEmphasisError? Material.Red : Material.accentColor
    Material.background: isEmphasisError? Material.Red : Material.backgroundColor
    Material.foreground: isEmphasisError? Material.Red : Material.foregroundColor

    Material.containerStyle: Material.Outlined
}
