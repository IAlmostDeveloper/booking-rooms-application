import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3
import AuthManager 1.0

Item{
    id: loginForm
    state: loginForm.width >= loginForm.height * 1.75 ? "Landscape" : "Portrait"
    states:[
        State{
            name: "Portrait"
            PropertyChanges {
                target: loginLayout
                columns: 1
            }
        },
        State{
            name: "Landscape"
            PropertyChanges {
                target: loginLayout
                columns: 4
            }
            AnchorChanges{
                target: loginLayout
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    ]

    Rectangle{
        width: parent.width
        height: parent.height
        anchors.fill: parent
        color: "#FF00F0"

        GridLayout{
             id: loginLayout
             columns: 1
             rowSpacing: 10
             columnSpacing: 20
             anchors.horizontalCenter: parent.horizontalCenter

             Text {
                 text: qsTr("SIGN IN")
                 Layout.alignment: Layout.Center
                 font{
                     pointSize: 25
                     family: "Helvetica"
                 }
             }

             TextField{
                id: signInLogin
                placeholderText: "Login"
             }

             TextField{
                id: signInPassword
                placeholderText: "Password"
                echoMode: TextField.Password
             }

             Button{
                 text: "Sign in"
                 Layout.alignment: Layout.Center
                 onClicked: {
                     authManager.auth(signInLogin.text, signInPassword.text);
                     clearFields();
                 }
                 enabled: signInLogin.text.length >= 5 && signInPassword.text.length >= 5
             }

             BusyIndicator{
                id: loginProcessing
                visible: authManager.isAuthProcessing
                Layout.alignment: Layout.Center
            }
        }
    }
    AuthManager{
        id: authManager
        onAuthFinished:{
            console.log("Auth finished!");
            console.log(token);
        }
        onAuthFailed: {
            console.log("Auth failed!");
            console.log(error);
            errorDialog.setInformativeText(error);
            errorDialog.open();
        }
    }

    function clearFields(){
        signInLogin.clear();
        signInPassword.clear();
    }
}
