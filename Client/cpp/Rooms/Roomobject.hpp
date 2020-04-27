#ifndef ROOMOBJECT_HPP
#define ROOMOBJECT_HPP

#include <QObject>

class RoomObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString hotel READ hotel WRITE setHotel NOTIFY hotelChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(bool available READ available WRITE setAvailable NOTIFY availableChanged)
public:
    explicit RoomObject(QObject *parent = nullptr);
    explicit RoomObject(int id, const QString& hotel,
                         const QString& description, bool available);
    int id();
    QString hotel();
    QString description();
    bool available();

    void setId(int value);
    void setHotel(const QString& value);
    void setDescription(const QString& value);
    void setAvailable(bool value);
signals:
    void idChanged(int id);
    void hotelChanged(const QString& hotel);
    void descriptionChanged(const QString& description);
    void availableChanged(bool available);
private:
    int m_id;
    QString m_hotel;
    QString m_description;
    bool m_available;
};

#endif // ROOMOBJECT_HPP
