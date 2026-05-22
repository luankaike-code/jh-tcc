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
    minimumHeight: 420
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

    QtObject {
        id: rootVariables

        property int mainControlSize: 350
        property int secondControlSize: mainControlSize/2
    }

    HomeWindowBackend {
        id: backend
        repositoryPath: dirPathInput.text
        imageDelay: { return parseInt(drawTimeInput.text) * 1000 }
        imageCount: { return parseInt(countRefInput.text) }
        sessionMode: { return parseInt(comboBoxSessionModes.currentValue) }
        roadmapDuration: { return parseInt(sessionDurationInput.text) * 1000 * 60 }


        onSessionStarted: root.hide()
        onSessionFinished: root.show()

        onErrorInvalidRepositoryPath: showError(qsTr("Repositório inválido"), dirPathInput)

        onErrorEmptyRepositoryPath: showError(qsTr("Insira o repositório"), dirPathInput)
        onErrorEmptyImageCount: showError(qsTr("Insira a quantidade de referência"), countRefInput)
        onErrorEmptyImageDelay: showError(qsTr("Insira o tempo de cada referência"), drawTimeInput)
        onErrorEmptyRoadmapDuration: showError(qsTr("Insira a duração total da sessão de aula"), sessionDurationInput)
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.minimumHeight: 45
        }

        RowLayout {
            Layout.minimumHeight: 45
            Layout.alignment: Qt.AlignHCenter

            Label {
                text: "FlashDraws"
                font.pixelSize: 22
                font.bold: true
            }
        }

        RowLayout {
            Layout.minimumHeight: 45
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.minimumHeight: 45

            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                RowLayout {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.minimumHeight: 45

                    Input {
                        id: dirPathInput

                        Layout.preferredWidth: rootVariables.mainControlSize
                        placeholderText: qsTr("Caminho para o repositorio de referência")
                    }
                }

                RowLayout {
                    Layout.alignment: Qt.AlignHCenter

                    GridLayout {
                        columns: 3

                        InputNumber {
                            id: drawTimeInput

                            visible: {
                                return SessionModeReader.hasTimerLimit(backend.sessionMode) && !SessionModeReader.hasRoadmap(backend.sessionMode)
                            }

                            Layout.preferredWidth: dirPathInput.width / 2 - parent.columnSpacing / 2
                            placeholderText: qsTr("tempo em segundos")
                        }

                        InputNumber {
                            id: countRefInput

                            visible: {
                                return SessionModeReader.hasImagesLimit(backend.sessionMode) && !SessionModeReader.hasRoadmap(backend.sessionMode)
                            }

                            Layout.alignment: Qt.AlignRight
                            Layout.preferredWidth: dirPathInput.width / 2 - parent.columnSpacing / 2
                            placeholderText: qsTr("qnt de refs")
                        }

                        InputNumber {
                            id: sessionDurationInput

                            visible: {
                                return SessionModeReader.hasRoadmap(backend.sessionMode)
                            }

                            Layout.preferredWidth: dirPathInput.width / 1.5
                            placeholderText: qsTr("tempo da sessão de aula em minutos")
                        }
                    }
                }

                RowLayout {
                    Layout.alignment: Qt.AlignHCenter

                    ColumnLayout {
                        RowLayout {
                            Layout.alignment: Qt.AlignHCenter

                            Label {
                                text: qsTr("Modo da Sessão")
                            }
                        }

                        RowLayout {
                            Layout.alignment: Qt.AlignHCenter

                            ComboBox {
                                id: comboBoxSessionModes
                                model: [
                                    { value: SessionModes.Normal, text: qsTr("Normal") },
                                    { value: SessionModes.Classroom, text: qsTr("Aula") },
                                    { value: SessionModes.InfinityTime, text: qsTr("Tempo Infinito") },
                                    { value: SessionModes.InfinityImages, text: qsTr("Referências Infinitas") },
                                    { value: SessionModes.Sandbox, text: qsTr("Sandbox") }
                                ]

                                Layout.preferredWidth: rootVariables.secondControlSize

                                textRole: "text"
                                valueRole: "value"
                            }
                        }
                    }
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.minimumHeight: 45

            Label {
                id: errorFeedback
                Material.foreground: Material.Red
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.minimumHeight: 20

            TimeDisplay {
                visible: {
                    return backend.sessionMode === SessionModes.Normal
                }

                value: {
                    let time = parseInt(drawTimeInput.text) || -1
                    let count = parseInt(countRefInput.text) || -1

                    return (time < 0 || count < 0)? 0 : time * count * 1000
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.minimumHeight: 45

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

        RowLayout {
            Layout.minimumHeight: 45
        }
    }
}