import QtQuick 2.0
import ".."

SimpleButton {
    property string text: ""
    property bool checked: false
    anchors.horizontalCenter: parent.horizontalCenter
    outline: false
    centerText: false

    Rectangle {
        height: parent.height / 2
        width: height
        color: "transparent"
        border.color: buttonColor
        border.width: 1
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        z: 10
        Text {
            text: "✓"
            color: buttonColor
            font.pointSize: 20
            visible: checked
            anchors.centerIn: parent
        }
    }

    onClicked: checked = !checked
}
