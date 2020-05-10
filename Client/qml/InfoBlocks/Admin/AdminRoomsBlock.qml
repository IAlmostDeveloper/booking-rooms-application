import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import App 1.0

Item {
    id: adminRoomsBlock
    state: adminRoomsBlock.width >= adminRoomsBlock.height * 1.75 ? "Landscape" : "Portrait"
    states:[
        State{
            name: "Portrait"
            PropertyChanges {
                target: fieldsLayout
                columns: 2
            }
        },
        State{
            name: "Landscape"
            PropertyChanges {
                target: fieldsLayout
                columns: 4
            }
        }
    ]

    Connections{
        target: App.roomsManager
        ignoreUnknownSignals: enabled

        onAddRoomSuccess: {
            console.log("added successfully");
        }
        onAddRoomError: {
            errorDialog.setInformativeText(error);
            errorDialog.open();
        }
    }

    GridLayout{
        id: fieldsLayout
        anchors{
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }

        columns: 4
        rows: 1
        columnSpacing: 10

        Column{
            spacing: 5
            Text{
                text: qsTr("Hotel name")
            }

            TextField{
              id: roomHotelNameField
            }
        }

        Column{
            spacing: 5
            Text{
                text: qsTr("Description")
            }

            TextField{
              id: roomDescriptionField
            }
        }

        Column{
            spacing: 5
            Text{
                text: qsTr("Available")
            }

            ComboBox{
                id: roomAvailableField
                model: ["Yes", "No"]
            }
        }

        Column{
            spacing: 10

            Text{
            }

            Button{
                id: addRoomButton
                text: qsTr("Add");
                enabled: roomHotelNameField.text.length!==0
                onClicked: {
                    App.roomsManager.addRoomToDatabase(roomHotelNameField.text,
                                                 roomDescriptionField.text,
                                                 roomAvailableField.currentText=="Yes");
                }
            }
        }
    }
}
