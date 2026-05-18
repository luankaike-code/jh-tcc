import QtQuick
import flashdraws

import "./components/sessionControlWindow"
import "./components/imagesWindow"
import "./components/dialogConfirmFinishSession"

Item {
    id: root
    required property var images
    required property int delayImages
    required property int imagesCount
    required property int sessionMode
    required property int roadmapDuration

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
            sessionControlWindow.show()
        }else {
            dialogConfirmFinishSession.show()
            imagesWindow.hide()
            sessionControlWindow.hide()
        }
    }

    function confirmSessionEnd() {
        sessionControlWindow.pauseTimer()
        windowsVisibility(false)
    }

    function updateImageOpacity() {
        if(!SessionModeReader.hasTimerLimit(sessionMode))
            return;

        const remainingTime = sessionControlWindow.timerRemainingTime
        const delayImages = sessionControlWindow.delayImages
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
            sessionControlWindow.playTimer()
        }
    }

    ImagesWindow {
        id: imagesWindow
        images: root.images

        onContextPopupOpened: sessionControlWindow.pauseTimer()
        onContextPopupClosed: sessionControlWindow.playTimer()

        onClosing: root.confirmSessionEnd()
    }

    SessionControlWindow {
        id: sessionControlWindow
        delayImages: root.delayImages
        imagesCount: root.imagesCount
        sessionMode: root.sessionMode
        roadmapDuration: root.roadmapDuration

        onFinishInterval: imagesWindow.nextImage()
        onNextImageButtonClicked: imagesWindow.nextImage()
        onPreventImageButtonClicked: imagesWindow.preventImage()
        onSessionFinished: root.finishSession()
        onFinishSessionButtonClicked: root.confirmSessionEnd()
        onTimerRemainingTimeChanged: root.updateImageOpacity()

        onClosing: root.confirmSessionEnd()
    }
}
