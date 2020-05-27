#include "Customcalendarmodel.hpp"

CustomCalendarModel::CustomCalendarModel()
{
    for(int i=1;i<31;i++)
        append(new CalendarDay(i, random() % 4 > 1));
}

int CustomCalendarModel::rowCount(const QModelIndex &parent) const
{
    return m_calendarDays.count();
}

QVariant CustomCalendarModel::data(const QModelIndex &index, int role) const
{
    if(index.row()>=0 && index.row() < m_calendarDays.count())
        switch(role){
            case CalendarRoles::Date :
                return m_calendarDays[index.row()]->date();
            case CalendarRoles::Available:
                return m_calendarDays[index.row()]->available();
            }
    return QVariant();
}

void CustomCalendarModel::append(CalendarDay* calendarDay)
{
    beginInsertRows(QModelIndex(), m_calendarDays.count(), m_calendarDays.count());
    m_calendarDays.append(calendarDay);
    endInsertRows();
}

void CustomCalendarModel::clear()
{
    beginResetModel();
    m_calendarDays.clear();
    endResetModel();
}

QHash<int, QByteArray> CustomCalendarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CalendarRoles::Date] = "date";
    roles[CalendarRoles::Available] = "available";
    return roles;
}
