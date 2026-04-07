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

    function nextImage() {
        refImg.setSrc(root.getRandomImage())
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

        property bool is_dragging: false
        property var mouse_delta: ({x: 0, y: 0})

        onReleased: {
            console.log("boi")
            is_dragging = false
        }

        onPressed: (mouse) => {
            console.log("oi", is_dragging)
            if(!is_dragging) {
                mouse_delta.x = mouse.x
                mouse_delta.y = mouse.y
                is_dragging = true
            }
        }

        onPositionChanged: (mouse) => {
            if(is_dragging){
                root.x += mouse.x - mouse_delta.x
                root.y += mouse.y - mouse_delta.y
            }
        }
    }
}
