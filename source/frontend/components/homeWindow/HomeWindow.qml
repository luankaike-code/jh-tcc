import QtQuick

import QtQuick.Controls
import QtQuick.Layouts
import flashdraws

import "../inputs"
import "../magnitudeDisplay"

ApplicationWindow {
    id: root
    width: 640
    height: 480
    minimumWidth: 400
    visible: true
    title: qsTr("FlashDraws")

    FilesGrabber {
        id: filesGrabber

        onGottedAllImagesAtFolder: (images) => handler.createFlashDrawSession(images)
        onInvalidDirectoryPath: (path) => handler.invalidDirectoryPath(path)
    }

    Item {
        id: handler

        function showError(mensage, inputToEmphasis=undefined) {
            errorFeedback.text = mensage

            if(inputToEmphasis)
                inputToEmphasis.isEmphasisError = true
        }

        function removeAllErrors() {
            dirPathInput.isEmphasisError = false
            drawTimeInput.isEmphasisError = false
            countRefInput.isEmphasisError = false
            errorFeedback.text = ""
        }

        function invalidDirectoryPath(path) {
            showError(qsTr("Caminho inválido: %1").arg(path), dirPathInput)
        }

        function tryStartFlashDrawSession() {
            removeAllErrors()
            if(!dirPathInput.text)
                showError(qsTr("Insira um repositorio"), dirPathInput)
            else if(!drawTimeInput.text)
                showError(qsTr("Preencha o tempo de cada FlashDraw"), drawTimeInput)
            else if(!countRefInput.text)
                showError(qsTr("Preencha a quantidade de FlashDraw"), countRefInput)
            else
                filesGrabber.getAllImagesAtFolder(dirPathInput.text) // onGottedAllImagesAtFolder -> createFlashDrawSession
        }

        function createFlashDrawSession(images) {
            let component = Qt.createComponent("../flashDrawSessionWindow/FlashDrawSessionWindow.qml")
            let instance = component.createObject(root, {
                "images": images,
                "delayImages": parseInt(drawTimeInput.text)*1000,
                "imagesCount": parseInt(countRefInput.text)
            })

            root.visible = false
            instance.sessionFinished.connect(() => {
                root.visible = true
            })
        }
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {}

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Label {
                text: "FlashDraws"
            }
        }

        RowLayout {}
        RowLayout {}


        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Input {
                id: dirPathInput

                Layout.preferredWidth: 350
                placeholderText: "Caminho para o repositorio de referência"
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            GridLayout {
                columns: 3

                InputNumber {
                    id: countRefInput
                    Layout.alignment: Qt.AlignRight
                    Layout.preferredWidth: dirPathInput.width / 2 - parent.columnSpacing / 2
                    placeholderText: "qnt de refs"
                }

                InputNumber {
                    id: drawTimeInput
                    Layout.preferredWidth: dirPathInput.width / 2 - parent.columnSpacing / 2
                    placeholderText: "tempo em segundos"
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Label {
                id: errorFeedback
                Material.foreground: Material.Red
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            MagnitudeDisplay {
                value: {
                    let time = parseInt(drawTimeInput.text) || -1
                    let count = parseInt(countRefInput.text) || -1

                    return (time < 0 || count < 0)? 0 : time * count
                }

                magnitudes: [
                    MagnitudeObj {
                        value: 1
                        symbol: "seg"
                    },
                    MagnitudeObj {
                        value: 60
                        symbol: "min"
                    },
                    MagnitudeObj {
                        value: 60*60
                        symbol: "horas"
                    },
                    MagnitudeObj {
                        value: 60*60*24
                        symbol: "dias"
                    }
                ]
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Button {
                width: 200
                height: 40
                text: qsTr("Iniciar")

                onClicked: handler.tryStartFlashDrawSession()
            }
        }

        RowLayout {}
    }
}