import QtQuick

import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt.labs.platform

Button {
    id: root
    property string choosedFolder

    text: qsTr("open")
    onClicked: folderDialog.open()

    FolderDialog {
        id: folderDialog
        onFolderChanged: root.choosedFolder = String(folder).split("file:///")[1]
    }
}
