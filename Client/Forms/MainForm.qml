import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import HotelsModel 1.0

Item {
    id: mainForm

    TabBar{
        id: tabBar
        width: parent.width
        anchors.top: parent.top

        TabButton{
            text: "Hotels"
            onClicked: {
                blockLoader.source = "HotelsBlock.qml"
            }
        }

        TabButton{
            text: "Rooms"
            onClicked: {
                blockLoader.source = "RoomsBlock.qml"
            }
        }

        TabButton{
            text: "Rents"
            onClicked: {
                blockLoader.source = "RentsBlock.qml"
            }
        }
    }

    Loader{
        id: blockLoader
        width: parent.width
        height: parent.height - tabBar.height - 20
        anchors.top: tabBar.bottom
        source: "HotelsBlock.qml"
    }

}
