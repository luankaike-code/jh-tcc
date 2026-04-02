import QtQuick 6.11

Window {
    id: root
    width: 350
    height: 350

    visible: true
    title: qsTr("FlashDraws Ref")
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    required property list<string> avaibleImages

    Component.onCompleted: {
        x = Screen.width
        y = 0

        refImg.setSrc(avaibleImages[0])
    }

    Image {
        id: refImg
        width: root.width
        height: root.height
        fillMode: Image.PreserveAspectFit

        function setSrc(image) {
            source = "file:///"+image
        }
    }

    Text {
        text: refImg.status === Image.Ready ? 'Loaded' : 'Not loaded'
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log(refImg.source)
            console.log(sourceRefImg)
            refImg.source = sourceRefImg
        }
    }
}
