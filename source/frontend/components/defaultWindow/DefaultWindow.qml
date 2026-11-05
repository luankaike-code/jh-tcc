// SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
    color: palette.window

    Material.theme: palette.window.r + palette.window.g + palette.window.b < 1.5 ? Material.Dark : Material.Light
    Material.accent: palette.highlight
    Material.primary: palette.window
    Material.background: palette.window
}
