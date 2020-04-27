import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Room 1.0
import App 1.0

Item {
    property string currentHotelName: ""
    id: roomsBlock
    width: parent.width
    height: parent.height

    function clearList(){
        tableModel.clear();
    }
    function getRoomsList(){
        var hotel = hotelNameField.text;
        App.roomsManager.getParsedRoomsList(onlyAvailableCheckbox.checked, hotel);
    }

    state: roomsBlock.width >= roomsBlock.height * 1.75 ? "Landscape" : "Portrait"
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
    }

//    RoomsModel{
//        id: roomsModel
//        onRoomsDataReceived: {
//            clearList();
//            for(var i=0;i<roomsData.length;i++){
//                tableModel.append({
//                                  idText: roomsData[i].id,
//                                  hotelNameText: roomsData[i].hotel,
//                                  descriptionText : roomsData[i].description,
//                                  availableText: roomsData[i].available ? "Yes" : "No"});
//            }
//        }

//        onRoomsDataReceiveError: {
//            errorDialog.setInformativeText(error);
//            errorDialog.open();
//        }

//        onAddRoomSuccess: {
//            console.log("added successfully");
//            getRoomsList();

//        }
//        onAddRoomError: {
//            errorDialog.setInformativeText(error);
//            errorDialog.open();
//        }
//    }

    Row{
        id: roomParametersRow
        spacing: 10
        width: parent.width / 2.5
        height: 50

        CheckBox{
            id: onlyAvailableCheckbox
            text: "Only available rooms"
            onCheckStateChanged: {
                getRoomsList();
            }
        }

        TextField{
            id: hotelNameField
            placeholderText: "hotel name"
            text: currentHotelName
            onTextChanged: {
                getRoomsList();
            }

        }

        Button {
            text: qsTr("Get rooms list")
            onClicked: {
                getRoomsList();
            }
        }

    }

    ListView {
        id: roomsListView
        height: parent.height - fieldsLayout.height - roomParametersRow.height
        ScrollBar.vertical: ScrollBar{

        }

        anchors.top: roomParametersRow.bottom
        anchors.left: parent.left
        anchors.right: parent.right
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
                        spacing: 20

                        Text{
                            id: description
                            width: parent.width / 4
                            text: descriptionText
                        }

                        Text{
                            id: hotel
                            width: parent.width / 4
                            text: hotelNameText
                        }

                        Column{
                            width: parent.width / 4
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
                            id: bookRoomButton
                            width: parent.width / 5
                            text: qsTr("Book")
                            onClicked: {
                                calendarDialog.open();
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
                text: qsTr("Hotel id")
            }

            TextField{
              id: roomHotelIdField
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
                enabled: !isNaN(roomHotelIdField.text) && roomHotelIdField.text.length!=0
                onClicked: {
                    roomsModel.addRoomToDatabase(roomHotelIdField.text,
                                                 roomDescriptionField.text,
                                                 roomAvailableField.currentText=="Yes");
                }
            }
        }
    }
    Dialog{
        id: calendarDialog
        title: qsTr("Select date")
        standardButtons: StandardButton.Cancel | StandardButton.Ok
        Calendar{
            id: calendar
            minimumDate: new Date()
            maximumDate: new Date(2020, 4, 31)
        }
        onAccepted: {
            console.log(Qt.formatDate(calendar.selectedDate, "dd-MM-yy"));
        }
    }
}
