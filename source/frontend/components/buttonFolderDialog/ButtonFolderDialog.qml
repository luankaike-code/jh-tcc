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

    FolderDialog {
        id: folderDialog
        onFolderChanged: root.choosedFolder = String(folder).split("file:///")[1]
    }
}
