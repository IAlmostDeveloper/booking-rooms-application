#ifndef HOTELOBJDECT_HPP
#define HOTELOBJDECT_HPP

#include <QObject>

class HotelObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(bool available READ available WRITE setAvailable NOTIFY availableChanged)
public:
    explicit HotelObject(QObject *parent = nullptr);
    explicit HotelObject(int id, const QString& name, const QString& address,
                         const QString& description, bool available);
    int id();
    QString name();
    QString address();
    QString description();
    bool available();

    void setId(int value);
    void setName(const QString& value);
    void setAddress(const QString& value);
    void setDescription(const QString& value);
    void setAvailable(bool value);

signals:
    void idChanged(int id);
    void nameChanged(const QString& name);
    void addressChanged(const QString& address);
    void descriptionChanged(const QString& description);
    void availableChanged(bool available);

private:
    int m_id;
    QString m_name;
    QString m_address;
    QString m_description;
    bool m_available;
};

#endif // HOTELOBJDECT_HPP
