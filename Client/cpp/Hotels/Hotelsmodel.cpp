#include "Hotelsmodel.hpp"

HotelsModel::HotelsModel()
{

}

HotelObject *HotelsModel::getHotel(int index)
{
    return m_hotels[index];
}

int HotelsModel::rowCount(const QModelIndex &parent) const
{
    return m_hotels.count();
}

QVariant HotelsModel::data(const QModelIndex &index, int role) const
{
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
//    beginResetModel();
//    m_hotels.clear();
//    endResetModel();
    beginRemoveRows(QModelIndex(), 0, m_hotels.count());
    for(int i=0;i<m_hotels.count();i++){
        removeRow(i);
        m_hotels[i]->deleteLater();
    }
    endRemoveRows();
}
