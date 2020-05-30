import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3
import App 1.0

Item{
    function clearFields(){
        signInLogin.clear();
        signInPassword.clear();
    }

    Component.onCompleted: {
        signInLogin.text = App.getPreviousSessionLogin();
        signInPassword.text = App.getPreviousSessionPassword();
    }

    signal successfulLogin();
    signal registerRequest();

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
                     App.authManager.auth(signInLogin.text, signInPassword.text);
                 }
                 enabled: signInLogin.text.length >= 5 && signInPassword.text.length >= 5
             }

             BusyIndicator{
                id: loginProcessing
                visible: App.authManager.isAuthProcessing
                Layout.alignment: Layout.Center
            }
        }

        Row{
            id: registerSuggestion
            anchors.top: loginLayout.bottom
            anchors.horizontalCenter: loginLayout.horizontalCenter
            anchors.topMargin: 30
            spacing: 10

            Text {
                text: qsTr("No account yet? ")
            }

            Text {
                text: qsTr("Sign Up")
                font.underline: enabled

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        registerRequest();
                    }
                    cursorShape: "PointingHandCursor"
                }
            }
        }

        Connections{
            target: App.authManager
            ignoreUnknownSignals: enabled
            onAuthFinished:{
                console.log("Auth finished!");
                console.log(token);
                App.saveSessionLogin(signInLogin.text);
                App.saveSessionPassword(signInPassword.text);
                clearFields();
                successfulLogin();
            }
            onAuthFailed: {
                console.log("Auth failed!");
                console.log(error);
                errorDialog.setInformativeText(error);
                errorDialog.open();
            }
        }
    }
}
