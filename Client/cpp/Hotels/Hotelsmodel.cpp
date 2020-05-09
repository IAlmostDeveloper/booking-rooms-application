#include "Hotelsmodel.hpp"

HotelsModel::HotelsModel()
{

}

HotelObject *HotelsModel::getHotel(int index)
{
    if(index<m_hotels.count())
        return m_hotels[index];
    return nullptr;
}

int HotelsModel::rowCount(const QModelIndex &parent) const
{
    return m_hotels.count();
}

QVariant HotelsModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >=0 && index.row()<m_hotels.count()){
        switch (role) {
            case HotelRoles::Id:
                return m_hotels[index.row()]->id();
            case HotelRoles::Name:
               return m_hotels[index.row()]->name();
            case HotelRoles::Address:
               return m_hotels[index.row()]->address();
            case HotelRoles::Description:
               return m_hotels[index.row()]->description();
            case HotelRoles::Available:
               return m_hotels[index.row()]->available();
        }
    }
    return QVariant();
}

void HotelsModel::append(HotelObject *hotel)
{
    beginInsertRows(QModelIndex(), m_hotels.count(), m_hotels.count());
    m_hotels.append(hotel);
    endInsertRows();
}

void HotelsModel::clear()
{
    beginResetModel();
    m_hotels.clear();
    endResetModel();
}

QHash<int, QByteArray> HotelsModel::roleNames() const
{
    QHash<int , QByteArray> hashset;
    hashset[HotelRoles::Id] = "id";
    hashset[HotelRoles::Name] = "name";
    hashset[HotelRoles::Address] = "address";
    hashset[HotelRoles::Description] = "description";
    hashset[HotelRoles::Available] = "available";
    return hashset;
}
