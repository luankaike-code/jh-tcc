import QtQuick 2.15
import QtQuick.Layouts 6.11
import QtQuick.Controls 6.11

Window {
    id: root
    width: 640
    height: 100
    minimumWidth: 400
    visible: true
    title: qsTr("FlashraDrawSession")
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    required property list<string> images

    Component.onCompleted: {
        x = Screen.width/2-width/2
        y = Screen.height-height-40

        let component = Qt.createComponent("../flashDrawWindow/FlashDrawWindow.qml")
        component.createObject(root, {
            "images": images
        })
    }

    RowLayout {
        anchors.fill: parent

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
}