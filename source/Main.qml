import QtQuick 6.11
import QtQuick.Controls 6.11
import QtQuick.Layouts 6.11

Window {
    width: 640
    height: 480
    minimumWidth: 400
    visible: true
    title: qsTr("FlashDraws")

    ColumnLayout {
        anchors.fill: parent

        RowLayout {}

        RowLayout {
           Layout.alignment: Qt.AlignHCenter

            Text {
                text: "FlashDraws"
            }
        }

        RowLayout {}
        RowLayout {}


        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            TextField {
                id: dirPathInput
                Layout.preferredWidth: 350
                placeholderText: "adivinha"
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            GridLayout {
                columns: 3

                TextField {
                    id: countRefInput
                    Layout.alignment: Qt.AlignRight
                    Layout.preferredWidth: dirPathInput.width / 2 - parent.columnSpacing / 2
                    placeholderText: "qnt de refs"

                    validator: RegularExpressionValidator {
                        regularExpression: /[0-9]+/
                    }
                    onTextChanged: {
                        sessionTimeText.newSessionTime()
                    }
                }

                TextField {
                    id: drawTimeInput
                    Layout.preferredWidth: dirPathInput.width / 2 - parent.columnSpacing / 2
                    placeholderText: "tempo em segundos"

                    validator: RegularExpressionValidator {
                        regularExpression: /[0-9]+/
                    }
                    onTextChanged: {
                        sessionTimeText.newSessionTime()
                    }
                }
            }
        }

        RowLayout {}

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Text {
                id: sessionTimeText
                text: qsTr("Tempo da sessão: ")

                function newSessionTime() {
                    let time = parseInt(drawTimeInput.text)
                    let count = parseInt(countRefInput.text)

                    time = time? time : 1
                    count = count? count : 1

                    let sessionTime = time * count
                    text = qsTr("Tempo da sessão: " + sessionTime + " seg")
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Button {
                width: 200
                height: 40
                text: qsTr("Iniciar")

                onClicked: {
                    console.log("path: " + dirPathInput.text)
                    console.log("refs: " + countRefInput.text)
                    console.log("time: " + drawTimeInput.text + " seg")
                }
            }
        }

        RowLayout {}
    }
}
