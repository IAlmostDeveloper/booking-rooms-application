import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Room 1.0
import App 1.0
import "../../Components/Calendar/"

Item {
    property string currentHotelName: ""
    property int roomIdToBook: 0
    id: roomsBlock
    width: parent.width
    height: parent.height

    function getRoomsList(){
        var hotel = hotelNameField.text;
        App.roomsManager.getParsedRoomsList(onlyAvailableCheckbox.checked, hotel);
    }

    Connections{
        target: App.roomsManager
        ignoreUnknownSignals: enabled

        onRoomsDataReceived: {
            console.log("rooms received")
        }

        onRoomsDataReceiveError: {
            errorDialog.setInformativeText(error);
            errorDialog.open();
        }
    }

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
        height: parent.height - roomParametersRow.height
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
                            text: model.description
                        }

                        Text{
                            id: hotel
                            width: parent.width / 4
                            text: model.hotel
                        }

                        Column{
                            width: parent.width / 4
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
                            id: bookRoomButton
                            width: parent.width / 5
                            text: qsTr("Book")
                            onClicked: {
                                roomIdToBook = model.id;
                                calendarDialog.open();
                                App.roomsManager.getRoomBookedDays(model.id);
                            }
                        }
                    }
                }
        }
        model: App.roomsManager.roomsModel
    }

    Dialog{
        id: calendarDialog
        width: 305
        height: 335
        title: qsTr("Select date")
        standardButtons: StandardButton.Cancel | StandardButton.Ok

        Rectangle{
            property var selectedDate: new Date()
            id: calendar
            width: parent.width
            height: parent.height
            border.color: "black"
            CustomCalendar{
                id: customCalendar
                anchors.fill: parent
                onDateSelected:{
                    calendar.selectedDate = selectedDate;
                    console.log(selectedDate);
                }
            }
        }
        onAccepted: {
            App.rentsManager.addUserRent(
                         roomIdToBook,
                         App.session.login,
                         Qt.formatDate(calendar.selectedDate, "dd-MM-yy"),
                         Qt.formatDate(calendar.selectedDate, "dd-MM-yy"))
        }
    }
}
