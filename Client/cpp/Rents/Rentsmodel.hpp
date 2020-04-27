#ifndef RENTSMODEL_HPP
#define RENTSMODEL_HPP

#include <QObject>

class RentsModel : public QObject
{
    Q_OBJECT
public:
    explicit RentsModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // RENTSMODEL_HPP