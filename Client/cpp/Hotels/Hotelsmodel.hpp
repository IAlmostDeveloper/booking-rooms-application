#ifndef HOTELSMODEL_HPP
#define HOTELSMODEL_HPP

#include <QAbstractListModel>
#include "Hotelobjdect.hpp"

class HotelsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit HotelsModel();
    Q_INVOKABLE HotelObject* getHotel(int index);
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    void append(HotelObject* hotel);
    Q_INVOKABLE void clear();

private:
    QList<HotelObject*> m_hotels;
};

#endif // HOTELSMODEL_HPP
