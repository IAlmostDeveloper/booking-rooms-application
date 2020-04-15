import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3
import AuthManager 1.0

Item {
    id:registrationForm
    state: registrationForm.width >= registrationForm.height * 1.5 ? "Landscape" : "Portrait"
    states:[
        State{
            name: "Portrait"
            PropertyChanges {
                target: registrationLayout
                columns: 1
            }
        },
        State{
            name: "Landscape"
            PropertyChanges {
                target: registrationLayout
                columns: 2
            }
            AnchorChanges{
                target: registrationLayout
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    ]
    Rectangle{
     id: signUpBlock
     width: parent.width
     height: parent.height
     anchors.fill: parent
     color: "#ff0000"

     GridLayout{
         id: registrationLayout
         columnSpacing: 20
         rowSpacing: 10
         anchors.horizontalCenter: parent.horizontalCenter
         Text {
             text: qsTr("SIGN UP")
             Layout.alignment: Layout.Center
             font{
                 pointSize: 25
                 family: "Helvetica"
             }
         }
         TextField{
            id: signUpLogin
            placeholderText: "Your login"
         }

         TextField{
            id: signUpPassword
            placeholderText: "Your password"
            echoMode: TextField.Password
         }
         TextField{
            id: signUpRepeatPassword
            placeholderText: "Repeat password"
            echoMode: TextField.Password
         }
         Button{
             text: "Sign up"
             Layout.alignment: Layout.Center
             onClicked: {
                regManager.reg(signUpLogin.text, signUpPassword.text);
                clearFields();
             }
             enabled: signUpLogin.text.length >= 5
                      && signUpPassword.text.length >= 5
                      && signUpPassword.text === signUpRepeatPassword.text
         }
         BusyIndicator{
            id: signUpProcessing
            visible: regManager.isRegProcessing
            Layout.alignment: Layout.Center
            }
        }
    }
    AuthManager{
        id: regManager
        onRegFinished:{
            console.log("Reg finished!");
        }
        onRegFailed: {
            console.log("Reg failed!");
            console.log(error);
            errorDialog.setInformativeText(error);
            errorDialog.open();
        }
    }

    function clearFields(){
        signUpLogin.clear();
        signUpPassword.clear();
        signUpRepeatPassword.clear();
    }
}
