import QtQuick

import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import flashdraws

import "../inputs"
import "../magnitudeDisplay"
import "../defaultWindow"

DefaultWindow {
    id: root
    width: 640
    height: 480
    minimumWidth: 400
    visible: true
    title: qsTr("FlashDraws")

    function removeAllErrors() {
        dirPathInput.isEmphasisError = false
        drawTimeInput.isEmphasisError = false
        countRefInput.isEmphasisError = false
        errorFeedback.text = ""
    }

    function showError(mensage, inputToEmphasis=undefined) {
        errorFeedback.text = mensage

        if(inputToEmphasis)
            inputToEmphasis.isEmphasisError = true
    }

    HomeWindowBackend {
        id: backend
        repositoryPath: dirPathInput.text
        imageDelay: { return parseInt(drawTimeInput.text) * 1000 }
        imageCount: { return parseInt(countRefInput.text) }

        onSessionStarted: root.hide()
        onSessionFinished: root.show()

        onErrorInvalidRepositoryPath: showError(qsTr("Repositório inválido"), dirPathInput)

        onErrorEmptyRepositoryPath: showError(qsTr("Insira o repositório"), dirPathInput)
        onErrorEmptyImageCount: showError(qsTr("Insira a quantidade de referência"), countRefInput)
        onErrorEmptyImageDelay: showError(qsTr("Insira o tempo de cada referência"), drawTimeInput)
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {}

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Label {
                text: "FlashDraws"
                font.pixelSize: 22
                font.bold: true
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

                onClicked: {
                    removeAllErrors()
                    backend.startSession()
                }
            }
        }

        RowLayout {}
    }
}