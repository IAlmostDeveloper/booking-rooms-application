#include "Rentsmodel.hpp"

RentsModel::RentsModel()
{

}

RentObject *RentsModel::getRent(int index)
{
    return m_rents[index];
}

int RentsModel::rowCount(const QModelIndex &parent) const
{
    return m_rents.count();
}

QVariant RentsModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= 0 && index.row() < m_rents.count()){
        switch(role){
            case RentRoles::Id:
                return m_rents[index.row()]->id();
            case RentRoles::RoomId:
                return m_rents[index.row()]->roomId();
            case RentRoles::UserId:
                return m_rents[index.row()]->userId();
            case RentRoles::FromDate:
                return m_rents[index.row()]->fromDate();
            case RentRoles::ToDate:
                return m_rents[index.row()]->toDate();
        }
    }
    return QVariant();
}

void RentsModel::append(RentObject *rent)
{
    beginInsertRows(QModelIndex(), m_rents.count(), m_rents.count());
    m_rents.append(rent);
    endInsertRows();
}

void RentsModel::clear()
{
    beginResetModel();
    m_rents.clear();
    endResetModel();
}

QHash<int, QByteArray> RentsModel::roleNames() const
{
    QHash<int, QByteArray> hashset;
    hashset[RentRoles::Id] = "id";
    hashset[RentRoles::RoomId] = "roomId";
    hashset[RentRoles::UserId] = "userId";
    hashset[RentRoles::FromDate] = "fromDate";
    hashset[RentRoles::ToDate] = "toDate";
    return hashset;
}
