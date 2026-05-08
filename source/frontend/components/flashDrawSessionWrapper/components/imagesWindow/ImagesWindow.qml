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
    property int currentIndex: imagesWindowBackend.currentIndex

    function setImageOpacity(opacity) {
        refImg.opacity = opacity
    }

    function nextImage() {
        imagesWindowBackend.nextImage();
    }

    function preventImage() {
        imagesWindowBackend.preventImage();
    }

    Component.onCompleted: {
        x = Screen.width-width+30
        y = 30

        imagesWindowBackend.nextImage();
    }

    ImagesWindowBackend {
        id: imagesWindowBackend

        images: root.images
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
                clipboard.text = imagesWindowBackend.currentImage
                clipboard.copyText()
            }
        }
        MenuSeparator {}
        MenuItem {
            enabled: contextMenu.hasMoreThatOneImage
            text: qsTr("Remover")
            onTriggered: {
                imagesWindowBackend.removeImageFromAllDatas(imagesWindowBackend.currentImage)
                nextImage();
            }
        }
    }

    Image {
        id: refImg
        width: root.width
        height: root.height
        fillMode: Image.PreserveAspectFit

        source: {
            return imagesWindowBackend.currentImage? "file:///"+imagesWindowBackend.currentImage : ""
        }
    }
}
