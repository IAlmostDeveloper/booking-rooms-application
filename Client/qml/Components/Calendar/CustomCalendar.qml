import QtQuick 2.0
import CustomCalendarModel 1.0
import App 1.0

Item {
    signal dateSelected(var selectedDate);
    property int selectedDate: 0
    property int cellSize : 40
    property var months: ["Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul","Aug","Sep", "Oct", "Nov", "Dec"]

    Connections{
        target: App.roomsManager
        onRoomBookedDaysReceiveSuccess:{
            customCalendarModel.bookedDays = bookedDays;
        }
    }

    Column{
        anchors.fill: parent
        Row{
            id: calendarSlider
            height: 25
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text {
                text: qsTr("Prev")
                font.underline: enabled
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        customCalendarModel.currentMonth = customCalendarModel.currentMonth - 1;
                    }
                    cursorShape: "PointingHandCursor"
                }
            }
            Text {
                text: qsTr(months[customCalendarModel.currentMonth-1] + " " + customCalendarModel.currentYear)
            }
            Text {
                text: qsTr("Next")
                font.underline: enabled
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        customCalendarModel.currentMonth = customCalendarModel.currentMonth + 1;
                    }
                    cursorShape: "PointingHandCursor"
                }
            }
        }
        Row{
            id: dayOfTheWeekRow
            height: 20
            Text{
                width: cellSize
                text: qsTr("Mon");
            }
            Text{
                width: cellSize
                text: qsTr("Tue");
            }
            Text{
                width: cellSize
                text: qsTr("Wed");
            }
            Text{
                width: cellSize
                text: qsTr("Thu");
            }
            Text{
                width: cellSize
                text: qsTr("Fri");
            }
            Text{
                width: cellSize
                text: qsTr("Sat");
            }
            Text{
                width: cellSize
                text: qsTr("Sun");
            }
        }

        GridView{
            width: parent.width
            height: parent.height- calendarSlider.height - dayOfTheWeekRow.height
            model: customCalendarModel
            cellWidth: cellSize
            cellHeight: cellSize
            delegate: Rectangle{
                width: cellSize
                height: cellSize
                color: model.date!== -1 && model.available ? "#0AFF00"
                       : model.date !== -1 && !model.available ? "red" : "transparent"
                border.color: selectedDate===model.date ? "black" : "transparent"
                Text {
                    id: date
                    text: model.date
                    color: model.date === -1 ? "transparent" : "black"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(model.available){
                            selectedDate = model.date;
                            dateSelected(new Date(customCalendarModel.currentYear,
                                              customCalendarModel.currentMonth-1,model.date));
                        }
                    }
                    cursorShape: model.available ? Qt.PointingHandCursor : Qt.ArrowCursor;
                }
            }
        }

        CustomCalendarModel{
            id: customCalendarModel
        }
    }
}
