import QtQuick 6.5
import "../draggableArea"

Window {
    id: root
    width: 350
    height: 350

    visible: true
    title: qsTr("FlashDraws Ref")
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    required property var images
    property var avaibleImages: []
    property var historycImages: []
    property int currentIndex: 0

    Component.onCompleted: {
        x = Screen.width-width
        y = 0

        nextImage()
    }

    function nextImage() {
        if(historycImages.length > 0)
            currentIndex++

        if(currentIndex < historycImages.length) {
            refImg.setSrc(historycImages[currentIndex])
            return
        }

        refImg.setSrc(getRandomImage())
    }

    function preventImage() {
        if(currentIndex < 0)
            return

        if(currentIndex > 0)
            currentIndex--

        refImg.setSrc(historycImages[currentIndex])
    }

    function getRandomImage() {

        if (avaibleImages.length == 0){
            avaibleImages = images.slice() // copy images
        }

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

    DraggableArea {
        onUpdateRealativeDragPosition: (x, y) => {
            root.x += x
            root.y += y
        }
    }
}
