import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import App 1.0

Item {
    id: adminHotelsBlock
    state: adminHotelsBlock.width >= adminHotelsBlock.height * 1.75 ? "Landscape" : "Portrait"

    Component.onCompleted: {
        App.hotelsManager.getParsedHotelsList();
    }

    Connections{
        target: App.hotelsManager
        ignoreUnknownSignals: enabled

        onAddHotelSuccess: {
            console.log("added successfully");
        }

        onAddHotelError: {
            errorDialog.setInformativeText(error);
            errorDialog.open();
        }
    }

    ListView {
        id: hotelsListView
        width: parent.width
        height: parent.height - addHotelButton.height
        ScrollBar.vertical: ScrollBar{}

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        delegate: Item {
                id: item
                width: parent.width
                anchors.left: parent.left
                anchors.right: parent.right
                height: 40

                Rectangle{
                    width: parent.width
                    anchors.fill: parent
                    color: "#ffff00"

                    Row{
                        width: parent.width
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 5

                        Text{
                            id: name
                            width: parent.width / 6
                            text: model.name
                        }

                        Text{
                            id: address
                            width: parent.width / 6
                            text: model.address
                        }

                        Text{
                            id: description
                            width: parent.width / 5
                            text: model.description
                        }

                        Column{
                            width: parent.width / 6
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
                            id: editHotelButton
                            width: parent.width / 10
                            text: "Edit"
                            onClicked: {

                            }
                        }

                        Button{
                            id: deleteHotelButton
                            width: parent.width / 10
                            text: "Delete"
                            onClicked: {

                            }
                        }
                    }
                }
            }
        model: App.hotelsManager.hotelsModel
    }

    Button{
        id: addHotelButton
        width: parent.width / 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: hotelsListView.bottom
        text: "Add hotel"
        onClicked: {
            addHotelDialog.open();
        }
    }

    Dialog{
        id: addHotelDialog
        width: 305
        height: 335
        title: qsTr("Add hotel")
        standardButtons: StandardButton.Cancel | StandardButton.Ok
        Column{
            id: fieldsLayout
            anchors{
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            spacing: 10
            Text{
                text: qsTr("Name")
            }

            TextField{
              id: hotelNameField
            }

            Text{
                text: qsTr("Address")
            }

            TextField{
              id: hotelAddressField
            }
            Text{
                text: qsTr("Available")
            }

            ComboBox{
                id: hotelAvailableField
                model: ["Yes", "No"]
            }

            Text{
                text: qsTr("Description")
            }

            TextField{
              id: hotelDescriptionField
            }
        }
        onAccepted: {
            App.hotelsManager.addHotelToDatabase(hotelNameField.text,
                                                               hotelAddressField.text,
                                                               hotelDescriptionField.text,
                                                               hotelAvailableField.currentText=="Yes")
        }
    }
}
