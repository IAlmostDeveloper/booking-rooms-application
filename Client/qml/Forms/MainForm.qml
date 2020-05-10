import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import App 1.0

Item {
    id: mainForm
    property bool showAdminBlocks : false
    Component.onCompleted: {
        showAdminBlocks = App.session.isAdmin;
        console.log(showAdminBlocks);
    }

    TabBar{
        id: tabBar
        width: parent.width
        anchors.top: parent.top

        TabButton{
            text: "Hotels"
            onClicked: {
                blockLoader.source = "qrc:/qml/InfoBlocks/User/UserHotelsBlock.qml"
            }
        }

        TabButton{
            text: "Rooms"
            onClicked: {
                blockLoader.source = "qrc:/qml/InfoBlocks/User/UserRoomsBlock.qml"
            }
        }

        TabButton{
            text: "Rents"
            onClicked: {
                blockLoader.source = "qrc:/qml/InfoBlocks/User/UserRentsBlock.qml"
            }
        }

        TabButton{
            text: "Hotels(Admin)"
            onClicked: {
                blockLoader.source = "qrc:/qml/InfoBlocks/Admin/AdminHotelsBlock.qml"
            }
            visible: showAdminBlocks
        }

        TabButton{
            text: "Rooms(Admin)"
            onClicked: {
                blockLoader.source = "qrc:/qml/InfoBlocks/Admin/AdminRoomsBlock.qml"
            }
            visible: showAdminBlocks
        }

        TabButton{
            text: "Rents(Admin)"
            onClicked: {
                blockLoader.source = "qrc:/qml/InfoBlocks/Admin/AdminRentsBlock.qml"
            }
            visible: showAdminBlocks
        }

    }

    Loader{
        id: blockLoader
        width: parent.width
        height: parent.height - tabBar.height - 20
        anchors.top: tabBar.bottom
        source: "qrc:/qml/InfoBlocks/User/UserHotelsBlock.qml"
    }

    Connections{
        target: blockLoader.item
        ignoreUnknownSignals: enabled
        onViewRoomsRequest:{
            blockLoader.source = "qrc:/qml/InfoBlocks/User/UserRoomsBlock.qml";
            target.currentHotelName = hotelName;
            tabBar.currentIndex = 1;
        }
    }
}
