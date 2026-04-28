import QtQuick 2.15

import "../flashDrawSessionWindow"
import "../flashDrawWindow"

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
        flashDrawWindow.visible = are_visible
        flashDrawWindow.visibility = are_visible? Window.Windowed : Window.Hidden

        flashDrawSessionWindow.visible = are_visible
        flashDrawSessionWindow.visibility = are_visible? Window.Windowed : Window.Hidden
    }

    function confirmSessionEnd() {
        windowsVisibility(false)
        flashDrawSessionWindow.pauseTimer()

        let component = Qt.createComponent("../flashDrawSessionWrapper/DialogConfirmFinishSession.qml")
        let instance = component.createObject(root)

        instance.confirm.connect(() => {
            sessionFinished()
            destroy()
        })

        instance.cancel.connect(() => {
            windowsVisibility(true)
            flashDrawSessionWindow.playTimer()
        })
    }

    FlashDrawWindow {
        id: flashDrawWindow
        images: root.images

        onClosing: root.confirmSessionEnd()
    }

    FlashDrawSessionWindow {
        id: flashDrawSessionWindow
        delayImages: root.delayImages
        imagesCount: root.imagesCount

        onFinishInterval: flashDrawWindow.nextImage()
        onNextImage: flashDrawWindow.nextImage()
        onPreventImage: flashDrawWindow.preventImage()
        onSessionFinished: root.finishSession()
        onFinishSessionBtnClicked: root.confirmSessionEnd()

        onClosing: root.confirmSessionEnd()
    }
}
