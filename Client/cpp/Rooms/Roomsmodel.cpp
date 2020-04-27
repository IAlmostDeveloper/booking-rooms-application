#include "Roomsmodel.hpp"

RoomsModel::RoomsModel()
{

}

RoomObject *RoomsModel::getRoom(int index)
{
    return m_rooms[index];
}

int RoomsModel::rowCount(const QModelIndex &parent) const
{
    return m_rooms.count();
}

QVariant RoomsModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

void RoomsModel::append(RoomObject *room)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_rooms.append(room);
    endInsertRows();
}
