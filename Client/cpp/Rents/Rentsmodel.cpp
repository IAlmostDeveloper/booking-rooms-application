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
    return QVariant();
}

void RentsModel::append(RentObject *rent)
{
    beginInsertRows(QModelIndex(), m_rents.count(), m_rents.count());
    m_rents.append(rent);
    endInsertRows();
}
