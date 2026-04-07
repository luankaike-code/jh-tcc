import QtQuick 2.15
import QtQuick.Layouts 6.11
import QtQuick.Controls 6.11
import flashdraws 0.1
import "../draggableArea"

Window {
    id: root
    width: 640
    height: 100
    minimumWidth: 400
    visible: true
    title: qsTr("FlashraDrawSession")
    flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    required property list<string> images
    property var flashDraw


    Component.onCompleted: {
        x = Screen.width/2-width/2
        y = Screen.height-height-40

        let component = Qt.createComponent("../flashDrawWindow/FlashDrawWindow.qml")
        flashDraw = component.createObject(root, {
            "images": images
        })

        timer.startRhythmIntervals(3000, 5)
    }

    Timer {
        id: timer
        onFinishInterval: {
            if(flashDraw){
                flashDraw.nextImage()
            }
        }
    }

    RowLayout {
        anchors.fill: parent

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
           Text {
               text: timer.remainingTime
           }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
           Button {
               text: "pause"
           }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
           Button {
               text: "retorne"
           }
        }
    }

    DraggableArea {
        onUpdateRealativeDragPosition: (x, y) => {
            root.x += x
            root.y += y
        }
    }
}