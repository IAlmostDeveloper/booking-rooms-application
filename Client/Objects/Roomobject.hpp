#ifndef ROOMOBJECT_HPP
#define ROOMOBJECT_HPP

#include <QObject>

class RoomObject : public QObject
{
    Q_OBJECT
public:
    explicit RoomObject(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ROOMOBJECT_HPP