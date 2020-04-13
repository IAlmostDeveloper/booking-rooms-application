#ifndef HOTELSMODEL_HPP
#define HOTELSMODEL_HPP

#include <QObject>

class HotelsModel : public QObject
{
    Q_OBJECT
public:
    explicit HotelsModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // HOTELSMODEL_HPP