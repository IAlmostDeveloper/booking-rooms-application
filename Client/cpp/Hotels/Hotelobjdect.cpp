#include "Hotelobjdect.hpp"

HotelObject::HotelObject(QObject *parent) : QObject(parent)
{

}

HotelObject::HotelObject(int id, const QString& name, const QString& address,
                         const QString& description, bool available)
{
    setId(id);
    setName(name);
    setAddress(address);
    setDescription(description);
    setAvailable(available);
}

QString HotelObject::name()
{
    return m_name;
}

QString HotelObject::address()
{
    return m_address;
}

QString HotelObject::description()
{
   return m_description;
}

int HotelObject::id()
{
    return m_id;
}

bool HotelObject::available()
{
    return m_available;
}

void HotelObject::setName(const QString &value)
{
    m_name = value;
    emit nameChanged(value);
}

void HotelObject::setAddress(const QString &value)
{
    m_address = value;
    emit addressChanged(value);
}

void HotelObject::setDescription(const QString &value)
{
    m_description = value;
    emit descriptionChanged(value);
}

void HotelObject::setId(int value)
{
    m_id = value;
    emit idChanged(value);
}

void HotelObject::setAvailable(bool value)
{
    m_available = value;
    emit availableChanged(value);
}
