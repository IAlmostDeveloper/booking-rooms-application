#include "Roomobject.hpp"

RoomObject::RoomObject(QObject *parent) : QObject(parent)
{

}

RoomObject::RoomObject(int id, const QString& hotel, const QString &description, bool available)
{
    setId(id);
    setHotel(hotel);
    setDescription(description);
    setAvailable(available);
}

int RoomObject::id()
{
    return m_id;
}

QString RoomObject::hotel()
{
    return m_hotel;
}

QString RoomObject::description()
{
    return m_description;
}

bool RoomObject::available()
{
    return m_available;
}

void RoomObject::setId(int value)
{
    m_id = value;
    emit idChanged(value);
}

void RoomObject::setHotel(const QString& value)
{
    m_hotel = value;
    emit hotelChanged(value);
}

void RoomObject::setDescription(const QString &value)
{
    m_description = value;
    emit descriptionChanged(value);
}

void RoomObject::setAvailable(bool value)
{
    m_available = value;
    emit availableChanged(value);
}
