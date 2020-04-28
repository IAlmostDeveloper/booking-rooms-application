import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import App 1.0

Item {
    id: mainForm
    TabBar{
        id: tabBar
        width: parent.width
        anchors.top: parent.top

        TabButton{
            text: "Hotels"
            onClicked: {
                blockLoader.source = "qrc:/qml/InfoBlocks/HotelsBlock.qml"
            }
        }

        TabButton{
            text: "Rooms"
            onClicked: {
                blockLoader.source = "qrc:/qml/InfoBlocks/RoomsBlock.qml"
            }
        }

        TabButton{
            text: "Rents"
            onClicked: {
                blockLoader.source = "qrc:/qml/InfoBlocks/RentsBlock.qml"
            }
        }
    }

    Loader{
        id: blockLoader
        width: parent.width
        height: parent.height - tabBar.height - 20
        anchors.top: tabBar.bottom
        source: "qrc:/qml/InfoBlocks/HotelsBlock.qml"
        onLoaded: {
            App.hotelsManager.setNewHotelsModel();
            App.roomsManager.setNewRoomsModel();
            App.rentsManager.setNewRentsModel();
        }
    }

    Connections{
        target: blockLoader.item
        ignoreUnknownSignals: enabled
        onViewRoomsRequest:{
            blockLoader.source = "qrc:/qml/InfoBlocks/RoomsBlock.qml";
            target.currentHotelName = hotelName;
            tabBar.currentIndex = 1;
        }
    }
}
