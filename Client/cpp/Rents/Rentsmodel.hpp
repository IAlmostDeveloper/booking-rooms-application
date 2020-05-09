#ifndef RENTSMODEL_HPP
#define RENTSMODEL_HPP

#include <QAbstractListModel>
#include "Rentobject.hpp"
class RentsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RentRoles {
        Id = 0,
        RoomId = 1,
        UserId = 2,
        FromDate = 3,
        ToDate = 4
    };
    explicit RentsModel();
    Q_INVOKABLE RentObject* getRent(int index);
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    void append(RentObject* rent);
    void clear();
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<RentObject*> m_rents;
};

#endif // RENTSMODEL_HPP
