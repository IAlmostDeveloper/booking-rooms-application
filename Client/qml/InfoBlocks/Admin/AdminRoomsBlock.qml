import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import App 1.0

Item {
    property int editingRoomId: -1
    id: adminRoomsBlock
    Component.onCompleted: {
        App.roomsManager.getParsedRoomsList(false, "");
    }

    Connections{
        target: App.roomsManager
        ignoreUnknownSignals: enabled
        onRoomsDataReceived: {
        }

        onRoomsDataReceiveError: {
            errorDialog.setInformativeText(error);
            errorDialog.open();
        }
        onAddRoomSuccess: {
            console.log("added successfully");
        }
        onAddRoomError: {
            errorDialog.setInformativeText(error);
            errorDialog.open();
        }
    }

    ListView {
        id: roomsListView
        width: parent.width
        height: parent.height - addRoomButton.height
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
                            id: description
                            width: parent.width / 4
                            text: model.description
                        }

                        Text{
                            id: hotel
                            width: parent.width / 5
                            text: model.hotel
                        }

                        Column{
                            width: parent.width / 5
                            spacing: 5
                            Text{
                                id: id
                                text: "Id: " + model.id
                            }

                            Text{
                                id: available
                                text: "Available: " + model.available
                            }
                        }
                        Button{
                            id: editRoomButton
                            width: parent.width / 10
                            text: "Edit"
                            onClicked: {
                                editingRoomId = model.id;
                                editRoomHotelNameField.text = model.hotel;
                                editRoomAvailableField.checked = model.available;
                                editRoomDescriptionField.text = model.description;
                                editRoomDialog.open();
                            }
                        }

                        Button{
                            id: deleteRoomButton
                            width: parent.width / 10
                            text: "Delete"
                            onClicked: {
                                App.roomsManager.deleteRoom(model.id);
                            }
                        }
                    }
                }
        }
        model: App.roomsManager.roomsModel
    }

    Button{
        id: addRoomButton
        text: "Add room"
        width: parent.width / 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: roomsListView.bottom
        onClicked: {
            addRoomDialog.open();
        }
    }

    Dialog{
        id: addRoomDialog
        width: 400
        height: 400
        standardButtons: StandardButton.Cancel | StandardButton.Ok
        onAccepted: {
            App.roomsManager.addRoomToDatabase(roomHotelNameField.text,
                                         roomDescriptionField.text,
                                         roomAvailableField.currentText=="Yes");
        }
        Column{
            id: fieldsLayout
            anchors{
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            Text{
                text: qsTr("Hotel name")
            }

            TextField{
              id: roomHotelNameField
            }

            Text{
                text: qsTr("Description")
            }

            TextField{
              id: roomDescriptionField
            }

            Text{
                text: qsTr("Available")
            }

            ComboBox{
                id: roomAvailableField
                model: ["Yes", "No"]
            }
        }
    }

    Dialog{
        id: editRoomDialog
        width: 400
        height: 400
        standardButtons: StandardButton.Cancel | StandardButton.Ok
        onAccepted: {
            App.roomsManager.editRoom(editingRoomId, editRoomHotelNameField.text,
                                         editRoomDescriptionField.text,
                                         editRoomAvailableField.checked);
        }
        Column{
            id: editFieldsLayout
            anchors{
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            Text{
                text: qsTr("Hotel name")
            }

            TextField{
              id: editRoomHotelNameField
              text: ""
            }

            Text{
                text: qsTr("Description")
            }

            TextField{
              id: editRoomDescriptionField
              text: ""
            }

            Text{
                text: qsTr("Available")
            }

            CheckBox{
                id: editRoomAvailableField
            }
        }
    }
}
