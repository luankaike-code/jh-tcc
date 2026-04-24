import QtQuick

MouseArea {
    anchors.fill: parent

    property bool isDraggable: true
    property bool isDragging: false
    property var mouseDelta: ({x: 0, y: 0})
    acceptedButtons: Qt.RightButton

    signal updateRealativeDragPosition(real x, real y)

    onReleased: {
        isDragging = false
    }

    onPressed: (mouse) => {
        if(!isDragging && isDraggable) {
            mouseDelta.x = mouse.x
            mouseDelta.y = mouse.y
            isDragging = true
        }
    }

    onPositionChanged: (mouse) => {
        if(isDragging){
            let x = mouse.x - mouseDelta.x
            let y = mouse.y - mouseDelta.y
            updateRealativeDragPosition(x, y)
        }
    }
}
