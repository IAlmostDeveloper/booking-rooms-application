import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3
import App 1.0

Item {
    signal successfulRegistration();

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

         TextField{
            id: signUpFirstName
            placeholderText: "First name"
         }

         TextField{
            id: signUpLastName
            placeholderText: "Last name"
         }

         TextField{
            id: signUpPassport
            placeholderText: "Passport"
         }

         Button{
             text: "Sign up"
             Layout.alignment: Layout.Center
             onClicked: {
                App.authManager.reg(signUpLogin.text, signUpPassword.text,
                               signUpFirstName.text, signUpLastName.text, signUpPassport.text);
                clearFields();
             }
             enabled: signUpLogin.text.length >= 5
                      && signUpPassword.text.length >= 5
                      && signUpPassword.text === signUpRepeatPassword.text
                      && signUpFirstName.text.length >= 2
                      && signUpLastName.text.length >= 2
                      && signUpPassport.text.length > 0
         }

         BusyIndicator{
            id: signUpProcessing
            visible: App.authManager.isRegProcessing
            Layout.alignment: Layout.Center
            }
        }

     Connections{
         target: App.authManager
         ignoreUnknownSignals: enabled
         onRegFinished:{
             console.log("Reg finished!");
             successfulRegistration();
         }
         onRegFailed: {
             console.log("Reg failed!");
             console.log(error);
             errorDialog.setInformativeText(error);
             errorDialog.open();
         }
      }
    }

    function clearFields(){
        signUpLogin.clear();
        signUpPassword.clear();
        signUpRepeatPassword.clear();
    }
}
