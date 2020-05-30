import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import App 1.0
import Rent 1.0
import Room 1.0

Item {
    Connections{
        target: App.rentsManager
        ignoreUnknownSignals: enabled
        onRentsDataReceived: {
        }
        onRentsDataReceiveError: {        
        }
    }

    Connections{
        target: App.roomsManager
        ignoreUnknownSignals: enabled
        onRoomDataReceived:{
            roomInfoDialogId.text = "Id: " + id;
            roomInfoDialogDescription.text = "Description: " + description;
            roomInfoDialogAvailable.text = "Available: " + (available ? "Yes" : "No");
            roomInfoDialogHotel.text = "Hotel: " + hotel;
        }
        onRoomDataReceiveError:{
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
        height: parent.height - rentsBlockText.height - userNameText.height - getRentsButton.height
        ScrollBar.vertical: ScrollBar{

        }

        anchors.top: getRentsButton.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        delegate: Item {
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
                            text: model.roomId
                        }

                        Text{
                            id: id
                            text: "Id: " + model.id
                            width: parent.width / 4
                        }

                        Column{
                            width: parent.width / 4
                            spacing: 5

                            Text{
                                id: fromDate
                                text: "From: " + model.fromDate
                            }

                            Text{
                                id: toDate
                                text: "To: " + model.toDate
                            }
                        }
                        Button{
                            id: moreRentInfoButton
                            width: parent.width / 5
                            text: qsTr("More")
                            onClicked: {
                                App.roomsManager.getRoom(model.roomId);
                                roomInfoDialog.open();
                            }
                        }
                    }
                }
        }

        model: App.rentsManager.rentsModel
    }

    Dialog{
        id: roomInfoDialog
        title: qsTr("Selected room")
        Column {
            spacing: 10

            Text{
                id: roomInfoDialogId
                text: "room.id"
            }

            Text{
                id: roomInfoDialogDescription
                text: "room.description"
            }

            Text{
                id: roomInfoDialogAvailable
                text: "room.available"
            }

            Text{
                id: roomInfoDialogHotel
                text: "room.hotel"
            }
        }
    }
}
