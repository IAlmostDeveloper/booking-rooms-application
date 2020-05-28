import QtQuick 2.0
import CustomCalendarModel 1.0

Item {
    property int selectedDate: -1
    property var months: ["jan", "feb", "mar", "apr", "may", "jun",
        "jul","aug","sep", "oct", "nov", "dec"]

    Column{
        anchors.fill: parent

        Row{
            id: calendarSlider
            height: 25
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text {
                text: qsTr("prev")
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        customCalendarModel.currentMonth = customCalendarModel.currentMonth - 1;
                    }
                }
            }
            Text {
                text: qsTr(months[customCalendarModel.currentMonth-1] + " " + customCalendarModel.currentYear)
            }
            Text {
                text: qsTr("next")
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        customCalendarModel.currentMonth = customCalendarModel.currentMonth + 1;
                    }
                }
            }
        }

        GridView{
            width: parent.width
            height: parent.height- calendarSlider.height
            model: customCalendarModel
            cellWidth: 40
            cellHeight: 40
            delegate: Rectangle{
                width: 40
                height: 40
                color: model.available ? "#0AFF00" : "red"
                border.color: selectedDate===model.date ? "black" : "transparent"
                    Text {
                        id: date
                        text: model.date
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log(model.date);
                            if(model.available)
                                selectedDate = model.date;
                        }
                    }
            }
        }

        CustomCalendarModel{
            id: customCalendarModel
        }
    }
}
