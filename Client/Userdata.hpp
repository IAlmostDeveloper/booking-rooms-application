#ifndef USERDATA_HPP
#define USERDATA_HPP

#include <QObject>

class UserData : public QObject
{
    Q_OBJECT
public:
    explicit UserData(QObject *parent = nullptr);
    Q_INVOKABLE QString getCurrentToken();
    Q_INVOKABLE QString getCurrentLogin();
};

#endif // USERDATA_HPP
