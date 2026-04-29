import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import flashdraws
import "../../../draggableArea"
import "../../../imageButton"
import "../../../magnitudeDisplay"

ApplicationWindow {
    id: root
    width: 640
    height: 100
    minimumWidth: 400
    visible: true
    title: qsTr("FlashraDrawSession")
    flags: Qt.WindowStaysOnTopHint

    required property int delayImages
    required property int imagesCount

    signal sessionFinished()
    signal finishInterval()
    signal nextImage()
    signal preventImage()
    signal finishSessionBtnClicked()

    Component.onCompleted: {
        x = Screen.width/2-width/2
        y = Screen.height-height-40

        timer.startRhythmIntervals(delayImages, imagesCount)
    }

    function finishSession() {
        sessionFinished()
        root.destroy()
    }

    function pauseTimer() {
        timer.stop()
    }

    function playTimer() {
        timer.play()
    }

    Timer {
        id: timer
        onFinishInterval: root.finishInterval()
        onFinishAllIntervals: root.finishSession()
    }

    RowLayout {
        anchors.fill: parent

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            MagnitudeDisplay {
                value: timer.remainingTime

                magnitudes: [
                    MagnitudeObj {
                        value: 1000
                        symbol: "seg"
                    }
                ]
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Label {
                text: qsTr("%1 / %2").arg(timer.currentInterval).arg(timer.intervalCount)
            }
        }

        ColumnLayout {
            ToggleButton {
                activedSource: "qrc:/qt/qml/flashdraws/assets/pause.svg"
                desactivedSource: "qrc:/qt/qml/flashdraws/assets/play.svg"

                onCheckedChanged: {
                    checked? playTimer() : pauseTimer()
                }

                height: 40
                width: 40
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            ImageButton {
                source: "qrc:/qt/qml/flashdraws/assets/double_arrow.svg"

                onClicked: {
                    timer.play(true)
                    root.preventImage()
                }

                mirror: true
                height: 40
                width: 40
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            ImageButton {
                source: "qrc:/qt/qml/flashdraws/assets/double_arrow.svg"

                onClicked: {
                    timer.play(true)
                    root.nextImage()
                }

                height: 40
                width: 40
           }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            ImageButton {
                source: "qrc:/qt/qml/flashdraws/assets/exit.svg"

                onClicked: root.finishSessionBtnClicked()

                height: 40
                width: 40
            }
        }
    }
}