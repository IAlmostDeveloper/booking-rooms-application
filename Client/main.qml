import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.1
import "qml"
import App 1.0

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
    property string currentForm: "SignIn"

    Loader{
        id: mainLoader
        anchors.fill: parent
        source: applicationForms[currentForm]
    }

    Connections{
        target: mainLoader.item
        ignoreUnknownSignals: enabled

        onSuccessfulLogin:{         
            currentForm = "Hotels";
        }

        onSuccessfulRegistration:{
            currentForm = "SignIn";
        }

        onLoginRequest:{
            currentForm = "SignIn"
        }

        onRegisterRequest:{
            currentForm = "SignUp";
        }

        onLogoutRequest:{
            App.clearUserData();
            currentForm = "SignIn";           
        }
    }

    MessageDialog{
        id: errorDialog
        title: "Error"
        text: "Error here!"
        icon: StandardIcon.Critical
   }
}
