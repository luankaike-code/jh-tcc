import QtQuick

Image {
    id: root
    sourceSize.width: width
    sourceSize.height: height

    signal clicked

    MouseArea {
        anchors.fill: root
        onClicked: {
            root.clicked()
        }
    }
}
