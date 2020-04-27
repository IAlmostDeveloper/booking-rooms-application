#ifndef ROOMSMODEL_HPP
#define ROOMSMODEL_HPP

#include <QAbstractListModel>
#include "Roomobject.hpp"

class RoomsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RoomsModel();
    Q_INVOKABLE RoomObject* getRoom(int index);
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    void append(RoomObject* room);

private:
    QList<RoomObject*> m_rooms;
};

#endif // ROOMSMODEL_HPP
