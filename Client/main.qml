import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.1

Window {
    id: root
    visible: true
    width: 320
    height: 600
    minimumWidth: 320
    minimumHeight: 400
    title: qsTr("Authorization")

    property var applicationForms: {
        "SignIn": "LoginForm.qml",
        "SignUp" : "RegisterForm.qml",
        "Hotels" : "HotelsForm.qml"
    }
    property bool isProcessingAuth : false

    Loader{
        id: mainLoader
        width: parent.width
        height: parent.height - bottomMenu.height
        anchors{
            bottom: bottomMenu.top
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }
        source: applicationForms[bottomMenu.pressedButton]
    }

    BottomMenu{
        id: bottomMenu
        anchors{
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
        }
    }

    MessageDialog{
        id: errorDialog
        title: "Error"
        text: "Error here!"
        icon: StandardIcon.Critical
        onAccepted: {
            isProcessingAuth = false;
      }
   }
}
