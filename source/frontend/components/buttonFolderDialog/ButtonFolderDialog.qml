import QtQuick

import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt.labs.platform

Item {
    id: root
    property string choosedFolder

    Button {
        text: qsTr("open")
        onClicked: folderDialog.open()
    }

    FolderDialog {
        id: folderDialog
        onFolderChanged: root.choosedFolder = String(folder).split("file:///")[1]
    }
}
