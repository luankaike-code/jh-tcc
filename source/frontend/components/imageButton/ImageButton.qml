import QtQuick
import QtQuick.Effects
import QtQuick.Controls
import QtQuick.Controls.Material

Image {
    id: root

    sourceSize.width: width
    sourceSize.height: height
    fillMode: Image.PreserveAspectFit

    signal clicked

    QtObject{
        id: variables

        property bool sourceIsSvg: false
    }

    onSourceChanged: {
        const strSource = String(source)
        const splitedSource = strSource.split(".")
        const sourceExtention = splitedSource[splitedSource.length-1]
        variables.sourceIsSvg = sourceExtention.toLowerCase() === "svg"
    }

    layer.enabled: variables.sourceIsSvg
    layer.effect: MultiEffect {
        colorization: 1.0
        colorizationColor: mouseArea.containsMouse? Material.accent : Material.foreground
    }

    MouseArea {
        id: mouseArea
        anchors.fill: root
        onClicked: {
            root.clicked()
        }
        hoverEnabled: true
    }
}
