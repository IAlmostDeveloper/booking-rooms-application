#ifndef RENTOBJECT_HPP
#define RENTOBJECT_HPP

#include <QObject>

class RentObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int roomId READ roomId WRITE setRoomId NOTIFY roomIdChanged)
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString fromDate  READ fromDate WRITE setFromDate NOTIFY fromDateChanged)
    Q_PROPERTY(QString toDate  READ toDate WRITE setToDate NOTIFY toDateChanged)

public:
    explicit RentObject(QObject *parent = nullptr);
    explicit RentObject(int id, int roomId, int userId,
                        const QString& fromDate, const QString& toDate);
    int id();
    int roomId();
    int userId();
    QString fromDate();
    QString toDate();

    void setId(int value);
    void setRoomId(int value);
    void setUserId(int value);
    void setFromDate(const QString& value);
    void setToDate(const QString& value);

signals:
    void idChanged(int id);
    void roomIdChanged(int roomId);
    void userIdChanged(int userId);
    void fromDateChanged(const QString& fromDate);
    void toDateChanged(const QString& toDate);

private:
    int m_id;
    int m_roomId;
    int m_userId;
    QString m_fromDate;
    QString m_toDate;
};

#endif // RENTOBJECT_HPP
