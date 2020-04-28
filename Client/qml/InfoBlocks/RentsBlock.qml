import QtQuick 2.0
import QtQuick.Controls 2.2
import App 1.0
import Rent 1.0

Item {
    Connections{
        target: App.rentsManager
        ignoreUnknownSignals: enabled
        onRentsModelChanged:{
            rentsListView.model = App.rentsManager.rentsModel;
        }

        onRentsDataReceived: {
            console.log("rents received");
        }
        onRentsDataReceiveError: {
            console.log("rents receive failed");
        }
    }

    Text{
        id: userNameText
        Component.onCompleted: {
            text = "Hello, " + App.session.login;
        }
    }

    Text {
        id: rentsBlockText
        text: qsTr("Here's block for rents info")
        anchors.top: userNameText.bottom
    }

    Button{
        id: getRentsButton
        anchors.top: rentsBlockText.bottom
        text: "Get my rents"
        onClicked: {
            App.rentsManager.getUserRents(App.session.login);
        }
    }

    ListView {
        id: rentsListView
        height: parent.height - rentsBlockText.height
        ScrollBar.vertical: ScrollBar{

        }

        anchors.top: getRentsButton.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        delegate: Item {
                property RentObject rent: App.rentsManager.rentsModel.getRent(index)
                id: item
                anchors.left: parent.left
                anchors.right: parent.right
                height: 40

                Rectangle{
                    anchors.fill: parent
                    color: "#ffff00"

                    Row{
                        width: parent.width
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 20

                        Text{
                            id: rentRoomId
                            width: parent.width / 4
                            text: rent.roomId
                        }

                        Text{
                            id: id
                            text: "Id: " + rent.id
                            width: parent.width / 4
                        }

                        Column{
                            width: parent.width / 4
                            spacing: 5

                            Text{
                                id: fromDate
                                text: "From: " + rent.fromDate
                            }

                            Text{
                                id: toDate
                                text: "To: " + rent.toDate
                            }
                        }
                        Button{
                            id: moreRentInfoButton
                            width: parent.width / 5
                            text: qsTr("More")
                            onClicked: {

                            }
                        }
                    }
                }
        }

        model: App.rentsManager.rentsModel
    }
}
