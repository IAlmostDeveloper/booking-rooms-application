import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import io.qt.models.hotels 1.0
Item {
    HotelsModel{
        id: hotelsModel
        onHotelsDataReceived: {
            for(var i=0;i<hotelsData.length;i++){
                console.log(hotelsData[i]);
                listModel.append({nameText: hotelsData[i].name,
                                  addressText: hotelsData[i].address,
                                  descriptionText: hotelsData[i].id,
                                  availableText:hotelsData[i].available,});
            }
        }
    }

    Button {
        id: getHotelsButton
        text: qsTr("Create Button")
        anchors.horizontalCenter: parent.horizontalCenter
        width: (parent.width / 5)*2
        height: 50

        onClicked: {
            hotelsModel.getParsedHotelsList();
        }
    }

    ListView {
        id: listView1

        anchors.top: getHotelsButton.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        delegate: Item {
            id: item
            anchors.left: parent.left
            anchors.right: parent.right
            height: 40

            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20
                Text{
                    id: name
                    text: nameText
                }

                Text{
                    id: address
                    text: addressText
                }

                Text{
                    id: description
                    text: descriptionText
                }
                Text{
                    id: available
                    text: availableText
                }
            }
        }

        model: ListModel {
            id: listModel
        }
    }
}
