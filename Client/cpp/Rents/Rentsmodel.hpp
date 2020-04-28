#ifndef RENTSMODEL_HPP
#define RENTSMODEL_HPP

#include <QAbstractListModel>
#include "Rentobject.hpp"
class RentsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RentsModel();
    Q_INVOKABLE RentObject* getRent(int index);
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    void append(RentObject* rent);
private:
    QList<RentObject*> m_rents;
};

#endif // RENTSMODEL_HPP
