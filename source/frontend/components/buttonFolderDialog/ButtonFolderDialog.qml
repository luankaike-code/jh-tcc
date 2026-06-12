import QtQuick

import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt.labs.platform

import "../imageButton"

ImageButton {
    id: root
    signal folderChoosed(string folderPath)

    source: "qrc:/assets/folder.svg"
    onClicked: folderDialog.open()

    FolderDialog {
        id: folderDialog

        function getValidFolderPath() {
            let strFolderPath = String(folderDialog.folder)
            let systemFolderPath = strFolderPath.split("file:///")[1]

            let validFolderPath = systemFolderPath
            if(Qt.platform.os === "linux" && systemFolderPath[0] !== "/")
                validFolderPath = "/"+validFolderPath

            return validFolderPath
        }

        onAccepted: {
            root.folderChoosed(getValidFolderPath())
        }
    }
}
