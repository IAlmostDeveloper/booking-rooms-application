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

void RoomsModel::clear()
{
    beginResetModel();
    m_rooms.clear();
    endResetModel();
}

QVariant RoomsModel::data(const QModelIndex &index, int role) const
{
    if(index.row()>=0 && index.row()<m_rooms.count()){
        switch(role){
        case RoomRoles::Id:
            return m_rooms[index.row()]->id();
        case RoomRoles::Hotel:
            return m_rooms[index.row()]->hotel();
        case RoomRoles::Description:
            return m_rooms[index.row()]->description();
        case RoomRoles::Available:
            return m_rooms[index.row()]->available();
        }
    }
    return QVariant();
}

void RoomsModel::append(RoomObject *room)
{
    beginInsertRows(QModelIndex(), m_rooms.count(), m_rooms.count());
    m_rooms.append(room);
    endInsertRows();
}

QHash<int, QByteArray> RoomsModel::roleNames() const
{
    QHash<int , QByteArray> hashset;
    hashset[RoomRoles::Id] = "id";
    hashset[RoomRoles::Hotel] = "hotel";
    hashset[RoomRoles::Description] = "description";
    hashset[RoomRoles::Available] = "available";
    return hashset;
}
