import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import flashdraws
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
    required property int roadmapDuration
    readonly property int timerRemainingTime: backend.remainingTime
    readonly property bool isRestPause: backend.isRestPause
    readonly property bool isStarted: backend.isStarted

    signal sessionFinished()
    signal finishInterval()
    signal nextImageButtonClicked()
    signal preventImageButtonClicked()
    signal finishSessionButtonClicked()

    Component.onCompleted: {
        x = Screen.width/2-width/2
        y = Screen.height-height-40
    }

    SessionControlWindowBackend {
        id: backend
        sessionModes: root.sessionMode
        imagesCount: root.imagesCount
        roadmapDuration: root.roadmapDuration
        delayImage: root.delayImages

        onGoToNextImage: root.nextImageButtonClicked()
        onGoToPreventImage: root.preventImageButtonClicked()
        onSessionFinish: root.finishSession()

        onTimerIsRunnigChanged: runTimeButton.checked = timerIsRunnig
    }

    function finishSession() {
        sessionFinished()
        root.destroy()
    }

    function pauseTimer() {
        backend.pauseTimer()
    }

    function playTimer() {
        backend.playTimer()
    }

    function resetTimer() {
        backend.resetTimer();
    }

    ColumnLayout {
        anchors.fill: parent
        visible: !backend.isStarted

        RowLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            Label {
                text: qsTr("Aperte quando estiver pronto")

                font.pixelSize: 22
                font.bold: true
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            ImageButton {
                source: "qrc:/qt/qml/flashdraws/assets/play-button.svg"

                onClicked: backend.startSession()

                height: 40
                width: 40
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        visible: backend.isRestPause

        RowLayout {
            visible: backend.hasTimerLimit || backend.hasRoadmap
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            Label {
                text: qsTr("Dê uma pausa. Relaxe")
            }
        }

        RowLayout {
            visible: backend.hasTimerLimit || backend.hasRoadmap
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            TimeDisplay {
                value: backend.remainingTime
                font.pixelSize: 22
                font.bold: true
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        visible: !backend.isRestPause && backend.isStarted

        ColumnLayout {
            visible: backend.hasTimerLimit || backend.hasRoadmap
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            TimeDisplay {
                value: backend.remainingTime
                font.pixelSize: 22
                font.bold: true
                Layout.minimumWidth: 100
            }
        }

        ColumnLayout {
            visible: backend.hasImagesLimit
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Label {
                text: qsTr("%1 / %2").arg(backend.currentImageIndex).arg(backend.imagesCount)
            }
        }

        ColumnLayout {
            visible: backend.hasTimerLimit
            ToggleButton {
                id: runTimeButton
                activedSource: "qrc:/qt/qml/flashdraws/assets/pause-button.svg"
                desactivedSource: "qrc:/qt/qml/flashdraws/assets/play-button.svg"

                checked: backend.timerIsRunnig

                onCheckedChanged: {
                    if(backend.isStarted)
                        checked? playTimer() : pauseTimer()
                }

                height: 40
                width: 40
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            ImageButton {
                source: "qrc:/qt/qml/flashdraws/assets/double-arrow-button.svg"

                onClicked: backend.preventButtonPressed()

                mirror: true
                height: 40
                width: 40
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            ImageButton {
                source: "qrc:/qt/qml/flashdraws/assets/double-arrow-button.svg"

                onClicked: backend.nextButtonPressed()

                height: 40
                width: 40
           }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            ImageButton {
                source: "qrc:/qt/qml/flashdraws/assets/exit-button.svg"

                onClicked: root.finishSessionButtonClicked()

                height: 40
                width: 40
            }
        }
    }
}