import QtQuick

import QtQuick.Controls
import QtQuick.Controls.Material
import flashdraws
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

    signal contextPopupOpened()
    signal contextPopupClosed()

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

    TapHandler {
        acceptedButtons: Qt.RightButton
        onTapped: {
            contextMenu.popup()
        }
    }

    Menu {
        id: contextMenu
        property bool hasMoreThatTwoImage: imagesWindowBackend.images.length > 2
        onOpened: {
            root.contextPopupOpened()
            hasMoreThatTwoImage = imagesWindowBackend.images.length > 2
        }

        onClosed: root.contextPopupClosed()

        MenuItem {
            text: qsTr("Copiar")
            onTriggered: imagesWindowBackend.copyCurrentImageToClipboard()
        }
        MenuSeparator {}
        MenuItem {
            enabled: contextMenu.hasMoreThatTwoImage
            text: qsTr("Remover")
            onTriggered: imagesWindowBackend.removeCurrentImage()
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
