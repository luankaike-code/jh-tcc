// SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick

import "../imageButton"

ImageButton {
    id: root

    required property string activedSource
    required property string desactivedSource
    property bool checked: true
    property bool changedFromClick: false

    source: checked? activedSource : desactivedSource

    sourceSize.width: width
    sourceSize.height: height

    onClicked: {
        changedFromClick = true
        checked = !checked
        changedFromClick = false
    }
}
