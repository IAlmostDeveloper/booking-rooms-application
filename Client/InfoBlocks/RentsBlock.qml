import QtQuick 2.0
import QtQuick.Controls 2.2
import RentsModel 1.0
import UserData 1.0

Item {
    Text{
        id: userNameText
        Component.onCompleted: {
            text = "Hello, " + userData.getCurrentLogin();
        }
    }

    Text {
        id: roomsBlockText
        text: qsTr("Here's block for rents info")
        anchors.top: userNameText.bottom
    }

    Button{
        anchors.top: roomsBlockText.bottom
        onClicked: {
            rentsModel.getUserRents(userData.getCurrentLogin());
        }
    }

    RentsModel{
        id: rentsModel
        onRentsDataReceived: {
            console.log("received!");
        }
        onRentsDataReceiveError: {
            console.log("failed!");
        }
    }

    UserData{
        id: userData
    }
}
