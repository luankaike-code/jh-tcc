import QtQuick

import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt.labs.platform

import "../imageButton"

ImageButton {
    id: root
    property string choosedFolder

    source: "qrc:/assets/folder.svg"
    onClicked: folderDialog.open()

    function getValidFolderPath() {
        let strFolderPath = String(folderDialog.folder)
        let systemFolderPath = strFolderPath.split("file:///")[1]

        let validFolderPath = systemFolderPath
        if(Qt.platform.os === "linux" && systemFolderPath[0] !== "/")
            validFolderPath = "/"+validFolderPath

        return validFolderPath
    }

    FolderDialog {
        id: folderDialog
        onFolderChanged: root.choosedFolder = getValidFolderPath()
    }
}
