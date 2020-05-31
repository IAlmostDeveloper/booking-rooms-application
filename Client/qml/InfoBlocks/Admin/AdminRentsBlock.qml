import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import App 1.0

Item {
    property int editingRentId : -1
    Component.onCompleted: {
        App.rentsManager.getAllRents();
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

    ListView {
        id: rentsListView
        width: parent.width
        height: parent.height - addRentButton.height
        ScrollBar.vertical: ScrollBar{}
        delegate:
            Item {
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
                        spacing: 5

                        Text{
                            id: rentRoomId
                            width: parent.width / 7
                            text: "Room id: " + model.roomId
                        }

                        Text{
                            id: id
                            text: "Id: " + model.id
                            width: parent.width / 7
                        }

                        Column{
                            width: parent.width / 5
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

                        Text {
                            id: userId
                            text: "User id: " + model.userId
                        }

                        Button{
                            id: moreRentInfoButton
                            width: parent.width / 7
                            text: qsTr("More")
                            onClicked: {
                                App.roomsManager.getRoom(model.roomId);
                                roomInfoDialog.open();
                            }
                        }

                        Button{
                            id: editRentButton
                            width: parent.width / 10
                            text: "Edit"
                            onClicked: {
                                editingRentId = model.id;
                                editRentRoomIdField.text = model.roomId;
                                editRentUserIdField.text = model.userId;
                                editRentFromDateField.text = model.fromDate;
                                editRentToDateField.text = model.toDate;
                                editRentDialog.open();
                            }
                        }

                        Button{
                            id: deleteRentButton
                            width: parent.width / 10
                            text: "Delete"
                            onClicked: {
                                App.rentsManager.deleteRent(model.id);
                            }
                        }
                    }
                }
        }

        model: App.rentsManager.rentsModel
    }

    Button{
        id: addRentButton
        text: "Add rent"
        width: parent.width / 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: rentsListView.bottom
        onClicked: {
            addRentDialog.open();
        }
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

    Dialog{
        id: addRentDialog
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        Column{
            Text{
                text: "roomId"
            }

            TextField{
                id: addRentRoomIdField
            }

            Text{
                text: "userId"
            }

            TextField{
                id: addRentUserIdField
            }

            Text{
                text: "fromDate"
            }

            TextField{
                id: addRentFromDateField
            }

            Text{
                text: "toDate"
            }

            TextField{
                id: addRentToDateField
            }
    }
        onAccepted: {
            App.rentsManager.addRent(addRentRoomIdField.text,
                                     addRentUserIdField.text,
                                     addRentFromDateField.text,
                                     addRentToDateField.text)
        }
    }

    Dialog{
        id: editRentDialog
        standardButtons: StandardButton.Ok | StandardButton.Cancel

        Column{
            Text{
                text: "roomId"
            }

            TextField{
                id: editRentRoomIdField
            }

            Text{
                text: "userId"
            }

            TextField{
                id: editRentUserIdField
            }

            Text{
                text: "fromDate"
            }

            TextField{
                id: editRentFromDateField
            }

            Text{
                text: "toDate"
            }

            TextField{
                id: editRentToDateField
            }
        }
        onAccepted: {
            App.rentsManager.editRent(editingRentId,
                                      editRentRoomIdField.text,
                                      editRentUserIdField.text,
                                      editRentFromDateField.text,
                                      editRentToDateField.text)
        }
    }
}
