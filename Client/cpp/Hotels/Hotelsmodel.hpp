#ifndef HOTELSMODEL_HPP
#define HOTELSMODEL_HPP

#include <QAbstractListModel>
#include "Hotelobjdect.hpp"

class HotelsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum HotelRoles{
        Id = 0,
        Name = 1,
        Address = 2,
        Description = 3,
        Available = 4

    };
    explicit HotelsModel();
    Q_INVOKABLE HotelObject* getHotel(int index);
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    void append(HotelObject* hotel);
    void clear();
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<HotelObject*> m_hotels;
};

#endif // HOTELSMODEL_HPP
