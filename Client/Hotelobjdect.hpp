#ifndef HOTELOBJDECT_HPP
#define HOTELOBJDECT_HPP

#include <QObject>

class HotelObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool available READ available WRITE setAvailable NOTIFY availableChanged)
public:
    explicit HotelObject(QObject *parent = nullptr);
    explicit HotelObject(const QString& name, const QString& address, int id, bool available);
    QString name();
    QString address();
    int id();
    bool available();

    void setName(const QString& value);
    void setAddress(const QString& value);
    void setId(int value);
    void setAvailable(bool value);

signals:
    void nameChanged(const QString& name);
    void addressChanged(const QString& address);
    void idChanged(int id);
    void availableChanged(bool available);

private:
    QString m_name;
    QString m_address;
    int m_id;
    bool m_available;
};

#endif // HOTELOBJDECT_HPP
