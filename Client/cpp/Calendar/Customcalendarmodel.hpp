#ifndef CUSTOMCALENDARMODEL_HPP
#define CUSTOMCALENDARMODEL_HPP

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "Calendarday.hpp"
#include <QDate>
#include "cpp/App.hpp"

class CustomCalendarModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int currentMonth READ currentMonth WRITE setCurrentMonth NOTIFY currentMonthChanged)
    Q_PROPERTY(int currentYear READ currentYear WRITE setCurrentYear NOTIFY currentYearChanged)
    Q_PROPERTY(QStringList bookedDays READ bookedDays WRITE setBookedDays NOTIFY bookedDaysChanged)
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
    QHash<int, QByteArray> roleNames() const override;

    QStringList bookedDays();
    void setBookedDays(QStringList bookedDays);

    void fillCalendar();
    int currentMonth();
    int currentYear();
    void setCurrentMonth(int month);
    void setCurrentYear(int year);
signals:
    void currentMonthChanged();
    void currentYearChanged();
    void bookedDaysChanged();

private:
    RoomsManager* m_roomsManager;
    QList<CalendarDay*> m_calendarDays;
    QDate m_currentDate;
    QStringList m_bookedDays;
};

#endif // CUSTOMCALENDARMODEL_HPP
