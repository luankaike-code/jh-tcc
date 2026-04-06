import QtQuick 6.11

Window {
    id: root
    width: 350
    height: 350

    visible: true
    title: qsTr("FlashDraws Ref")
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    required property list<string> images
    property list<string> avaibleImages: []
    property list<string> historycImages: []

    Component.onCompleted: {
        x = Screen.width-width
        y = 0

        refImg.setSrc(getRandomImage())
    }

    function getRandomImage() {

        if (avaibleImages.length == 0)
            avaibleImages = images

        const randAvaibleImageIndex = Math.floor(Math.random() * avaibleImages.length)
        const selectImage = avaibleImages.splice(randAvaibleImageIndex, 1)[0]
        historycImages.push(selectImage)
        return selectImage
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
            refImg.setSrc(root.getRandomImage())
        }
    }
}
