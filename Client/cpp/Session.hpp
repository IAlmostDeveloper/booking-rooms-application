#ifndef SESSION_HPP
#define SESSION_HPP

#include <QObject>

class Session : public QObject
{
    Q_OBJECT
public: 
    explicit Session();
    Session(const QString token, const QString &login, bool isAdmin);
    QString currentToken();
    QString currentLogin();
    bool isAdmin();
private:
    QString m_currentToken;
    QString m_currentLogin;
    bool m_isAdmin;
};

#endif // SESSION_HPP
