import QtQuick

import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import "../../../defaultWindow"

DefaultWindow {
    id: root
    minimumWidth: 300
    minimumHeight: 100
    title: qsTr("Encerrar a sessão atual?")

    signal confirm
    signal cancel

    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint

    Component.onCompleted: {
        x = Screen.width/2-width/2
        y = Screen.height/2-height/2
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
                        confirm()
                    }
                }
            }

            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                Button {
                    text: qsTr("Cancelar")
                    onClicked: {
                        cancel()
                    }
                }
            }
        }
    }
}
