import QtQuick 6.11

Window {
    width: 350
    height: 350

    visible: true
    title: qsTr("FlashDraws Ref")
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    Component.onCompleted: {
        x = Screen.width
        y = 0
    }
}
