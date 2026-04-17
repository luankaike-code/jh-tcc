import QtQuick 2.15
import QtQuick.Layouts 6.5
import QtQuick.Controls 6.5
import flashdraws 1.0
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
    required property int delayImages
    required property int imagesCount
    property var flashDraw

    signal sessionFinished()


    Component.onCompleted: {
        x = Screen.width/2-width/2
        y = Screen.height-height-40

        let component = Qt.createComponent("../flashDrawWindow/FlashDrawWindow.qml")
        flashDraw = component.createObject(root, {
            "images": images
        })

        timer.startRhythmIntervals(delayImages, imagesCount)
    }

    function finishSession() {
        sessionFinished()
        root.destroy()
    }

    Timer {
        id: timer
        onFinishInterval: {
            if(flashDraw){
                flashDraw.nextImage()
            }
        }
        onFinishAllIntervals: root.finishSession()
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
           Text {
               text: qsTr("%1 / %2").arg(timer.currentInterval).arg(timer.intervalCount)
           }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
           Button {
               text: "pause"
               onClicked: {
                   timer.stop()
               }
           }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
           Button {
               text: "retorne"
               onClicked: {
                   timer.play()
               }
           }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
           Button {
               text: "anterior"
               onClicked: {
                   timer.play(true)
                   flashDraw.preventImage()
               }
           }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
           Button {
               text: "próximo"
               onClicked: {
                   timer.play(true)
                   flashDraw.nextImage()
               }
           }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
           Button {
               text: "encerrar sessão"
               onClicked: root.finishSession()
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