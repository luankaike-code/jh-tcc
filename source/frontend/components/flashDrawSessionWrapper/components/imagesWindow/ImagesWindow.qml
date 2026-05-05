import QtQuick

import QtQuick.Controls
import QtQuick.Controls.Material
import flashdraws
import "../../../draggableArea"
import "../../../defaultWindow"

DefaultWindow {
    id: root
    minimumWidth: 350
    minimumHeight: 350

    visible: true
    title: qsTr("FlashDraws Ref")
    flags: Qt.WindowStaysOnTopHint | Qt.Window | Qt.WindowTitleHint

    required property var images
    property var avaibleImages: []
    property var historycImages: []
    property int currentIndex: 0

    Component.onCompleted: {
        x = Screen.width-width+30
        y = 30

        nextImage()
    }

    function nextImage() {
        if(historycImages.length > 0)
            currentIndex++

        if(currentIndex < historycImages.length) {
            refImg.sourcePath = historycImages[currentIndex]
            return
        }

        refImg.sourcePath = getRandomImage()
    }

    function preventImage() {
        if(currentIndex < 0)
            return

        if(currentIndex > 0)
            currentIndex--

        refImg.sourcePath = historycImages[currentIndex]
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

    function setImageOpacity(opacity) {
        refImg.opacity = opacity
    }

    function removeDataImage(path) {
        const isPathEqual = (x) => x === path
        const datas = [images, historycImages, avaibleImages]

        for(let dataIndex in datas) {
            let data = datas[dataIndex]
            let index = data.findIndex(isPathEqual)
            data.splice(index, 1)
        }

        if(path === refImg.sourcePath)
            nextImage()
    }

    Clipboard {
        id: clipboard
    }

    TapHandler {
        acceptedButtons: Qt.RightButton
        onTapped: {
            contextMenu.popup()
        }
    }

    Menu {
        id: contextMenu
        property bool hasMoreThatOneImage: root.images.length > 2
        onOpened: hasMoreThatOneImage = root.images.length > 2

        MenuItem {
            text: qsTr("Copiar")
            onTriggered: {
                clipboard.text = refImg.sourcePath
                clipboard.copyText()
            }
        }
        MenuSeparator {}
        MenuItem {
            enabled: contextMenu.hasMoreThatOneImage
            text: qsTr("Remover")
            onTriggered: removeDataImage(refImg.sourcePath)
        }
    }

    Image {
        id: refImg
        width: root.width
        height: root.height
        fillMode: Image.PreserveAspectFit

        property string sourcePath

        source: "file:///"+sourcePath
    }
}
