import QtQuick 2.0

Rectangle{
    width: parent.width
    height: 20
    property string pressedButton: "SignIn"

    Row{
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 3

        BottomMenuButton{
            text: qsTr("Sign in")
            name: "SignIn"
            font.underline: pressedButton==="SignIn"
            onBtnClicked: {
                pressedButton = name
            }
        }

        Text {
            text: qsTr("/")
        }

        BottomMenuButton{
            text: qsTr("Sign up")
            name: "SignUp"
            font.underline: pressedButton==="SignUp"
            onBtnClicked: {
                pressedButton = name
            }
        }

        Text {
            text: qsTr("/")
        }

        BottomMenuButton{
            text: qsTr("Hotels")
            name: "Hotels"
            font.underline: pressedButton==="Hotels"
            onBtnClicked: {
                pressedButton = name
            }
        }
    }
}
