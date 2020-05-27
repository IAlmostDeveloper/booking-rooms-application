#ifndef CUSTOMCALENDARMODEL_HPP
#define CUSTOMCALENDARMODEL_HPP

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "Calendarday.hpp"

class CustomCalendarModel : public QAbstractListModel
{
    Q_OBJECT
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

private:
    QList<CalendarDay*> m_calendarDays;
};

#endif // CUSTOMCALENDARMODEL_HPP
