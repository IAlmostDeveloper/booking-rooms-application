import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import App 1.0
import Hotel 1.0

Item {
    signal viewRoomsRequest(string hotelName)

    id: hotelsBlock
    width: parent.width
    height: parent.height

    Connections{
        target: App.hotelsManager
        ignoreUnknownSignals: enabled
        onHotelsDataReceived: {
            console.log("hotels received");
        }

        onHotelsDataReceiveError: {
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
            App.hotelsManager.getParsedHotelsList();
        }
    }

    ListView {
        id: hotelsListView
        width: parent.width
        height: parent.height - getHotelsButton.height
        ScrollBar.vertical: ScrollBar{
        }

        anchors.top: getHotelsButton.bottom
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
                        spacing: 20

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

        model: App.hotelsManager.hotelsModel
    }
}