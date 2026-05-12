import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import flashdraws
import "../../../draggableArea"
import "../../../imageButton"
import "../../../magnitudeDisplay"
import "../../../defaultWindow"

DefaultWindow {
    id: root
    width: 640
    height: 100
    minimumWidth: 400
    visible: true
    title: qsTr("FlashraDrawSession")
    flags: Qt.WindowStaysOnTopHint | Qt.Window | Qt.WindowTitleHint

    required property int delayImages
    required property int imagesCount
    required property int sessionMode
    readonly property int timerRemainingTime: timer.remainingTime

    signal sessionFinished()
    signal finishInterval()
    signal nextImageButtonClicked()
    signal preventImageButtonClicked()
    signal finishSessionButtonClicked()

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

        onIsRunningChanged: {
            runTimeButton.checked = timer.isRunning
        }
    }

    RowLayout {
        anchors.fill: parent

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            MagnitudeDisplay {
                value: timer.remainingTime
                font.pixelSize: 22
                font.bold: true

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
                id: runTimeButton
                activedSource: "qrc:/qt/qml/flashdraws/assets/pause.svg"
                desactivedSource: "qrc:/qt/qml/flashdraws/assets/play.svg"

                checked: timer.isRunning

                onCheckedUpdate: {
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
                    root.preventImageButtonClicked()
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
                    root.nextImageButtonClicked()
                }

                height: 40
                width: 40
           }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            ImageButton {
                source: "qrc:/qt/qml/flashdraws/assets/exit.svg"

                onClicked: root.finishSessionButtonClicked()

                height: 40
                width: 40
            }
        }
    }
}