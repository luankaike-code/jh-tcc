import QtQuick

import "./components/flashDrawSessionControlWindow"
import "./components/imagesWindow"
import "./components/dialogConfirmFinishSession"

Item {
    id: root
    required property var images
    required property int delayImages
    required property int imagesCount

    signal sessionFinished

    Component.onCompleted: {
        dialogConfirmFinishSession.visibility = Window.Hidden
    }

    function finishSession() {
        sessionFinished()
        destroy()
    }

    function windowsVisibility(are_visible) {
        if(are_visible){
            dialogConfirmFinishSession.hide()
            imagesWindow.show()
            flashDrawSessionControlWindow.show()
        }else {
            dialogConfirmFinishSession.show()
            imagesWindow.hide()
            flashDrawSessionControlWindow.hide()
        }
    }

    function confirmSessionEnd() {
        flashDrawSessionControlWindow.pauseTimer()
        windowsVisibility(false)
    }

    DialogConfirmFinishSession {
        id: dialogConfirmFinishSession

        onConfirm: {
            root.sessionFinished()
            root.destroy()
        }

        onCancel: {
            root.windowsVisibility(true)
            flashDrawSessionControlWindow.playTimer()
        }
    }

    ImagesWindow {
        id: imagesWindow
        images: root.images

        onClosing: root.confirmSessionEnd()
    }

    FlashDrawSessionControlWindow {
        id: flashDrawSessionControlWindow
        delayImages: root.delayImages
        imagesCount: root.imagesCount

        onFinishInterval: imagesWindow.nextImage()
        onNextImage: imagesWindow.nextImage()
        onPreventImage: imagesWindow.preventImage()
        onSessionFinished: root.finishSession()
        onFinishSessionBtnClicked: root.confirmSessionEnd()

        onClosing: root.confirmSessionEnd()
    }
}
