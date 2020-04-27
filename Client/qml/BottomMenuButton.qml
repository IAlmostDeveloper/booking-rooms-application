import QtQuick 2.0

Text {
    property string name: ""
    signal btnClicked();
    MouseArea{
        width: parent.width
        height: parent.height
        id: buttonMouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: buttonMouseArea.containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
        onClicked: {
            btnClicked()
        }
    }
}
