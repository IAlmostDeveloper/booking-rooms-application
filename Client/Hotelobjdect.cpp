#include "Hotelobjdect.hpp"

HotelObject::HotelObject(QObject *parent) : QObject(parent)
{

}

HotelObject::HotelObject(const QString &name, const QString &address, int id, bool available)
{
    setName(name);
    setAddress(address);
    setId(id);
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
