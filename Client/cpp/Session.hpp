#ifndef SESSION_HPP
#define SESSION_HPP

#include <QObject>

class Session : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
public: 
    explicit Session();
    Session(const QString token, const QString &login, bool isAdmin);
    QString token();
    QString login();
    void setToken(const QString& token);
    void setLogin(const QString& login);
    bool isAdmin();
signals:
    void tokenChanged();
    void loginChanged();
    void isAdminChanged();
private:
    QString m_token;
    QString m_login;
    bool m_isAdmin;
};

#endif // SESSION_HPP
