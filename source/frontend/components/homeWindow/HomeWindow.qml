import QtQuick 2.15

import QtQuick.Controls 6.11
import QtQuick.Layouts 6.11
import flashdraws 0.1

Window {
    id: root
    width: 640
    height: 480
    minimumWidth: 400
    visible: true
    title: qsTr("FlashDraws")

    GetterFiles {
        id: getterFiles

        onGottedAllImagesAtFolder: (images) => {
            let component = Qt.createComponent("../flashDrawSessionWindow/FlashDrawSessionWindow.qml")
            let instance = component.createObject(root, {
                "images": images,
                "delayImages": parseInt(drawTimeInput.text)*1000,
                "imagesCount": parseInt(countRefInput.text)
            })
        }
    }

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
                }

                TextField {
                    id: drawTimeInput
                    Layout.preferredWidth: dirPathInput.width / 2 - parent.columnSpacing / 2
                    placeholderText: "tempo em segundos"

                    validator: RegularExpressionValidator {
                        regularExpression: /[0-9]+/
                    }
                }
            }
        }

        RowLayout {}

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Text {
                id: sessionTimeText
                text: {
                    let time = parseInt(drawTimeInput.text) || -1
                    let count = parseInt(countRefInput.text) || -1

                    if (time < 0 || count < 0)
                        return qsTr("")

                    let sessionTime = time * count

                    let magnitude_relation
                    let magnitude_symbol

                    if (sessionTime < 60) {
                        magnitude_relation = 1
                        magnitude_symbol = "seg"
                    } else if (sessionTime < 3600) {
                        magnitude_relation = 60
                        magnitude_symbol = "min"
                    } else if (sessionTime < 86400) {
                        magnitude_relation = 3600
                        magnitude_symbol = "h"
                    } else {
                        magnitude_relation = 86400
                        magnitude_symbol = "dia"
                    }

                    sessionTime /= magnitude_relation

                    return qsTr("Tempo da sessão: %1 %2").arg(sessionTime.toFixed(1)).arg(magnitude_symbol)
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
                    getterFiles.getAllImagesAtFolder(dirPathInput.text)
                }
            }
        }

        RowLayout {}
    }
}