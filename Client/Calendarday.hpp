#ifndef CALENDARDAY_HPP
#define CALENDARDAY_HPP

#include <QObject>

class CalendarDay : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(bool available READ available WRITE setAvailable NOTIFY availableChanged)
public:
    explicit CalendarDay(int date, bool available);
    int date();
    void setDate(int date);
    bool available();
    void setAvailable(bool available);
signals:
    void dateChanged();
    void availableChanged();
private:
    int m_date;
    bool m_available;

};

#endif // CALENDARDAY_HPP
