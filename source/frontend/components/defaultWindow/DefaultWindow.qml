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
