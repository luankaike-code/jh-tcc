import QtQuick

import "./components/flashDrawSessionControlWindow"
import "./components/imagesWindow"

Item {
    id: root
    required property var images
    required property int delayImages
    required property int imagesCount

    signal sessionFinished

    function finishSession() {
        sessionFinished()
        destroy()
    }

    function windowsVisibility(are_visible) {
        imagesWindow.visible = are_visible
        imagesWindow.visibility = are_visible? Window.Windowed : Window.Hidden

        flashDrawSessionControlWindow.visible = are_visible
        flashDrawSessionControlWindow.visibility = are_visible? Window.Windowed : Window.Hidden
    }

    function confirmSessionEnd() {
        windowsVisibility(false)
        flashDrawSessionControlWindow.pauseTimer()

        let component = Qt.createComponent("./components/dialogConfirmFinishSession/DialogConfirmFinishSession.qml")
        let instance = component.createObject(root)

        instance.confirm.connect(() => {
            sessionFinished()
            destroy()
        })

        instance.cancel.connect(() => {
            windowsVisibility(true)
            flashDrawSessionControlWindow.playTimer()
        })
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
