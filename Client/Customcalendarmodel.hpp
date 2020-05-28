#ifndef CUSTOMCALENDARMODEL_HPP
#define CUSTOMCALENDARMODEL_HPP

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "Calendarday.hpp"
#include <QDate>

class CustomCalendarModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int currentMonth READ currentMonth WRITE setCurrentMonth NOTIFY currentMonthChanged)
    Q_PROPERTY(int currentYear READ currentYear WRITE setCurrentYear NOTIFY currentYearChanged)

public:
    explicit CustomCalendarModel();
    enum CalendarRoles{
        Date = 0,
        Available = 1
    };
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    void append(CalendarDay *calendarDay);
    void clear();
    void fillCalendar();
    QHash<int, QByteArray> roleNames() const override;

    int currentMonth();
    int currentYear();
    void setCurrentMonth(int month);
    void setCurrentYear(int year);
signals:
    void currentMonthChanged();
    void currentYearChanged();

private:
    QList<CalendarDay*> m_calendarDays;
    QDate m_currentDate;
};

#endif // CUSTOMCALENDARMODEL_HPP
