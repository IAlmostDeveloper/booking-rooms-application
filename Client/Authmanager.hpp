#ifndef AUTHMANAGER_HPP
#define AUTHMANAGER_HPP

#include <QObject>

class AuthManager : public QObject
{
    Q_OBJECT
public:
    explicit AuthManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // AUTHMANAGER_HPP