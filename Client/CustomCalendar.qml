import QtQuick 2.0
import CustomCalendarModel 1.0

Item {
    property int selectedDate: -1
    Column{
        anchors.fill: parent
        GridView{
            anchors.fill: parent
            model: CustomCalendarModel{}
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
    }
}
