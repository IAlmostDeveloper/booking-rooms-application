#include "Rentobject.hpp"

RentObject::RentObject(QObject *parent) : QObject(parent)
{

}

RentObject::RentObject(int id, int roomId, int userId, const QString& fromDate, const QString& toDate)
{
    setId(id);
    setRoomId(roomId);
    setUserId(userId);
    setFromDate(fromDate);
    setToDate(toDate);
}

int RentObject::id()
{
    return m_id;
}

int RentObject::roomId()
{
    return m_roomId;
}

int RentObject::userId()
{
    return m_userId;
}

QString RentObject::fromDate()
{
    return m_fromDate;
}

QString RentObject::toDate()
{
    return m_toDate;
}

void RentObject::setId(int value)
{
    m_id = value;
    emit idChanged(value);
}

void RentObject::setRoomId(int value)
{
    m_roomId = value;
    emit roomIdChanged(value);
}

void RentObject::setUserId(int value)
{
    m_userId = value;
    emit userIdChanged(value);
}

void RentObject::setFromDate(const QString &value)
{
    m_fromDate = value;
    emit fromDateChanged(value);
}

void RentObject::setToDate(const QString &value)
{
    m_toDate = value;
    emit toDateChanged(value);
}
