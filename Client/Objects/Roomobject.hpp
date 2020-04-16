#ifndef ROOMOBJECT_HPP
#define ROOMOBJECT_HPP

#include <QObject>

class RoomObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int hotelId READ hotelId WRITE setHotelId NOTIFY hotelIdChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(bool available READ available WRITE setAvailable NOTIFY availableChanged)
public:
    explicit RoomObject(QObject *parent = nullptr);
    explicit RoomObject(int id, int hotelId,
                         const QString& description, bool available);
    int id();
    int hotelId();
    QString description();
    bool available();

    void setId(int value);
    void setHotelId(int value);
    void setDescription(const QString& value);
    void setAvailable(bool value);
signals:
    void idChanged(int id);
    void hotelIdChanged(int hotelId);
    void descriptionChanged(const QString& description);
    void availableChanged(bool available);
private:
    int m_id;
    int m_hotelId;
    QString m_description;
    bool m_available;
};

#endif // ROOMOBJECT_HPP
