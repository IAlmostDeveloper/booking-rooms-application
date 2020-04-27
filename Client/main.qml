import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.1
import "qml"
Window {
    id: root
    visible: true
    width: 640
    height: 480
    minimumWidth: 460
    minimumHeight: 420
    title: qsTr("Booking rooms app")

    property var applicationForms: {
        "SignIn": "qml/Forms/LoginForm.qml",
        "SignUp" : "qml/Forms/RegisterForm.qml",
        "Hotels" : "qml/Forms/MainForm.qml"
    }

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

    Connections{
        target: mainLoader.item
        ignoreUnknownSignals: enabled
        onSuccessfulLogin:{
            bottomMenu.pressedButton = "Hotels";
        }
        onSuccessfulRegistration:{
            bottomMenu.pressedButton = "SignIn";
        }
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
   }
}
