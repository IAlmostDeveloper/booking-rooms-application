import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import App 1.0
Item {
    id: adminHotelsBlock
    state: adminHotelsBlock.width >= adminHotelsBlock.height * 1.75 ? "Landscape" : "Portrait"
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
                    App.hotelsManager.addHotelToDatabase(hotelNameField.text,
                                                   hotelAddressField.text,
                                                   hotelDescriptionField.text,
                                                   hotelAvailableField.currentText=="Yes")
                }
            }
        }
    }
}
