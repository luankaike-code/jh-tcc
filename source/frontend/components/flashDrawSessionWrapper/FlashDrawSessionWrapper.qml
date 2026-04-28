import QtQuick 2.15

import "../flashDrawSessionWindow"
import "../flashDrawWindow"

Item {
    id: root
    required property var images
    required property int delayImages
    required property int imagesCount

    signal sessionFinished

    FlashDrawWindow {
        id: flashDrawWindow
        images: root.images
    }

    FlashDrawSessionWindow {
        delayImages: root.delayImages
        imagesCount: root.imagesCount

        onFinishInterval: flashDrawWindow.nextImage()
        onNextImage: flashDrawWindow.nextImage()
        onPreventImage: flashDrawWindow.preventImage()
        onSessionFinished: root.sessionFinished()
    }
}
