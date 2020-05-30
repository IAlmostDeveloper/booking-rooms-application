#include "Customcalendarmodel.hpp"

CustomCalendarModel::CustomCalendarModel()
{
    m_currentDate = QDate::currentDate();
    connect(this, &CustomCalendarModel::bookedDaysChanged, &CustomCalendarModel::fillCalendar);
}

int CustomCalendarModel::currentMonth()
{
    return m_currentDate.month();
}

int CustomCalendarModel::currentYear()
{
    return m_currentDate.year();
}

void CustomCalendarModel::setCurrentMonth(int month)
{
    if(month==m_currentDate.month()) return;
    if(month>m_currentDate.month())
        m_currentDate = m_currentDate.addMonths(month-m_currentDate.month());
    if(month<m_currentDate.month())
        m_currentDate = m_currentDate.addMonths(month-m_currentDate.month());
    emit currentMonthChanged();
    fillCalendar();
}

void CustomCalendarModel::setCurrentYear(int year)
{

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

void CustomCalendarModel::fillCalendar()
{
    int currentMonth = m_currentDate.month();
    int currentDayOfWeek = m_currentDate.dayOfWeek();
    clear();
    for(int i=0;i<currentDayOfWeek-1;i++)
        append(new CalendarDay(-1, false));
    while(m_currentDate.month()==currentMonth){
        bool state = true;
        for(auto day : m_bookedDays){
            QString currentDate = m_currentDate.toString("dd-MM-yy");
            if(day==currentDate){
                state=false;
                break;
            }
        }
        append(new CalendarDay(m_currentDate.day(), state));
        m_currentDate = m_currentDate.addDays(1);
    }
    m_currentDate = m_currentDate.addMonths(-1);
}

QHash<int, QByteArray> CustomCalendarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CalendarRoles::Date] = "date";
    roles[CalendarRoles::Available] = "available";
    return roles;
}

QStringList CustomCalendarModel::bookedDays()
{
    return m_bookedDays;
}

void CustomCalendarModel::setBookedDays(QStringList bookedDays)
{
    m_bookedDays = bookedDays;
    emit bookedDaysChanged();
}
