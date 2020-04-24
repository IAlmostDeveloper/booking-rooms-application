#ifndef USERDATA_HPP
#define USERDATA_HPP

#include <QObject>

class Userdata : public QObject
{
    Q_OBJECT
public:
    explicit Userdata(QObject *parent = nullptr);

signals:

public slots:
};

#endif // USERDATA_HPP