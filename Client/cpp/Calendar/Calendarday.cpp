#include "Calendarday.hpp"

CalendarDay::CalendarDay(int date, bool available)
{
    m_date = date;
    m_available = available;
}

int CalendarDay::date()
{
    return m_date;
}

void CalendarDay::setDate(int date)
{
    m_date = date;
    emit dateChanged();
}

bool CalendarDay::available()
{
    return m_available;
}

void CalendarDay::setAvailable(bool available)
{
    m_available = available;
    emit availableChanged();
}
