import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    Text{
        id: userNameText
        Component.onCompleted: {
            text = "Hello, " + userData.getCurrentLogin();
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
        onClicked: {
            rentsModel.getUserRents(userData.getCurrentLogin());
        }
    }

//    RentsModel{
//        id: rentsModel
//        onRentsDataReceived: {
//            console.log("received!");
//            for(var i in rentsData){
//                console.log(rentsData[i]);
//                tableModel.append({
//                                  idText: rentsData[i].id,
//                                  roomIdText: rentsData[i].roomId,
//                                  fromDateText: rentsData[i].fromDate,
//                                  toDateText: rentsData[i].toDate
//                                  })
//            }
//        }
//        onRentsDataReceiveError: {
//            console.log("failed!");
//        }
//    }

//    UserData{
//        id: userData
//    }

    ListView {
        id: rentsListView
        height: parent.height - roomsBlockText.height - rentsBlockText.height
        ScrollBar.vertical: ScrollBar{

        }

        anchors.top: getRentsButton.bottom
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
                            id: rentRoomId
                            width: parent.width / 4
                            text: roomIdText
                        }

                        Text{
                            id: id
                            text: "Id: " + idText
                            width: parent.width / 4
                        }

                        Column{
                            width: parent.width / 4
                            spacing: 5

                            Text{
                                id: fromDate
                                text: "From: " + fromDateText
                            }

                            Text{
                                id: toDate
                                text: "To: " + toDateText
                            }
                        }
                        Button{
                            id: bookRoomButton
                            width: parent.width / 5
                            text: qsTr("More")
                            onClicked: {

                            }
                        }
                    }
                }
        }

        model: ListModel {
            id: tableModel
        }
    }
}
