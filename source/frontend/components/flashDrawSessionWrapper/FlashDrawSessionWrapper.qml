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
        dialogConfirmFinishSession.hide()
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

    function updateImageOpacity() {
        const remainingTime = flashDrawSessionControlWindow.timerRemainingTime
        const delayImages = flashDrawSessionControlWindow.delayImages
        const transitionFactor = 0.30

        let timeToStartTransition = delayImages*transitionFactor
        timeToStartTransition = timeToStartTransition > 10*1000? 10*1000 : timeToStartTransition

        if(remainingTime < timeToStartTransition)
            imagesWindow.setImageOpacity(remainingTime / timeToStartTransition)
        else
            imagesWindow.setImageOpacity(1)
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

        onContextPopupOpened: flashDrawSessionControlWindow.pauseTimer()
        onContextPopupClosed: flashDrawSessionControlWindow.playTimer()

        onClosing: root.confirmSessionEnd()
    }

    FlashDrawSessionControlWindow {
        id: flashDrawSessionControlWindow
        delayImages: root.delayImages
        imagesCount: root.imagesCount

        onFinishInterval: imagesWindow.nextImage()
        onNextImageButtonClicked: imagesWindow.nextImage()
        onPreventImageButtonClicked: imagesWindow.preventImage()
        onSessionFinished: root.finishSession()
        onFinishSessionButtonClicked: root.confirmSessionEnd()
        onTimerRemainingTimeChanged: root.updateImageOpacity()

        onClosing: root.confirmSessionEnd()
    }
}
