import QtQuick

import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow {
    id: root
    visible: true
    minimumWidth: 300
    minimumHeight: 100
    title: qsTr("Encerrar a sessão atual?")

    signal confirm
    signal cancel

    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint

    Component.onCompleted: {
        x = Screen.width/2-width/2
        y = Screen.height/2-height/2

        visible = true
        visibility = Window.Windowed
    }

    ColumnLayout {
        anchors.fill: parent
        Layout.alignment: Qt.AlignCenter

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Label {
                text: qsTr("Deseja mesmo encerrar sessão?")
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                Button {
                    text: qsTr("Confimar")
                    onClicked: {
                        root.destroy()
                        confirm()
                    }
                }
            }

            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                Button {
                    text: qsTr("Cancelar")
                    onClicked: {
                        root.destroy()
                        cancel()
                    }
                }
            }
        }
    }
}
