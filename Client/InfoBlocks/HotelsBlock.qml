import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import HotelsModel 1.0

Item {
    signal viewRoomsRequest(string hotelName)
    id: hotelsBlock
    width: parent.width
    height: parent.height

    function clearList(){
        tableModel.clear();
    }

    state: hotelsBlock.width >= hotelsBlock.height * 1.75 ? "Landscape" : "Portrait"
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

    HotelsModel{
        id: hotelsModel
        onHotelsDataReceived: {
            clearList();
            for(var i=0;i<hotelsData.length;i++){
                tableModel.append({
                                  idText: hotelsData[i].id,
                                  nameText: hotelsData[i].name,
                                  addressText: hotelsData[i].address,
                                  descriptionText : hotelsData[i].description,
                                  availableText: hotelsData[i].available ? "Yes" : "No"});
            }
        }

        onHotelsDataReceiveError: {
            errorDialog.setInformativeText(error);
            errorDialog.open();
        }

        onAddHotelSuccess: {
            console.log("added successfully");
            hotelsModel.getParsedHotelsList();

        }
        onAddHotelError: {
            errorDialog.setInformativeText(error);
            errorDialog.open();
        }
    }

    Button {
        id: getHotelsButton
        text: qsTr("Get hotels list")
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width / 2.5
        height: 50

        onClicked: {
            hotelsModel.getParsedHotelsList();
        }
    }

    ListView {
        id: hotelsListView
        width: parent.width
        height: parent.height - fieldsLayout.height - getHotelsButton.height
        ScrollBar.vertical: ScrollBar{

        }

        anchors.top: getHotelsButton.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        delegate:
            Item {
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
                        spacing: 20

                        Text{
                            id: name
                            width: parent.width / 6
                            text: nameText
                        }

                        Text{
                            id: address
                            width: parent.width / 6
                            text: addressText
                        }

                        Text{
                            id: description
                            width: parent.width / 5
                            text: descriptionText
                        }

                        Column{
                            width: parent.width / 6
                            spacing: 5
                            Text{
                                id: id
                                text: "Id: " + idText
                            }
                            Text{
                                id: available
                                text: "Available: " + availableText
                            }
                        }

                        Button{
                            id: viewHotelRoomsButton
                            text: "View rooms"
                            width: parent.width / 7
                            onClicked: {
                                console.log("view rooms");
                                viewRoomsRequest(name.text);
                            }
                        }
                    }
                }
        }

        model: ListModel {
            id: tableModel
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
                text: qsTr("Name")
            }

            TextField{
              id: hotelNameField
            }
        }

        Column{
            spacing: 5
            Text{
                text: qsTr("Address")
            }

            TextField{
              id: hotelAddressField
            }
        }

        Column{
            spacing: 5
            Text{
                text: qsTr("Available")
            }

            ComboBox{
                id: hotelAvailableField
                model: ["Yes", "No"]
            }
        }

        Column{
            spacing: 5
            Text{
                text: qsTr("Description")
            }

            TextField{
              id: hotelDescriptionField
            }
        }


        Column{
            spacing: 10

            Text{
            }

            Button{
                id: addHotelButton
                text: qsTr("Add");
                onClicked: {
                    hotelsModel.addHotelToDatabase(hotelNameField.text,
                                                   hotelAddressField.text,
                                                   hotelDescriptionField.text,
                                                   hotelAvailableField.currentText=="Yes")
                }
            }
        }
    }
}
