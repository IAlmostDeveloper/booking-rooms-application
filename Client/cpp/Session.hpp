#ifndef SESSION_HPP
#define SESSION_HPP

#include <QObject>
#include <QNetworkAccessManager>

class Session : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(bool isAdmin READ isAdmin WRITE setIsAdmin NOTIFY isAdminChanged)

public: 
    explicit Session(QObject* parent);
    Session(const QString token, const QString &login, bool isAdmin);
    bool isValid() const;
    QString token();
    QString login();
    bool isAdmin();

    void setToken(const QString& token);
    void setLogin(const QString& login);
    void setIsAdmin(bool isAdmin);

    void setIsValid(bool isValid);
    void getUserRights();

signals:
    void tokenChanged();
    void loginChanged();
    void isAdminChanged();

    void userRightsReceiveSuccess(const QString& rights);
    void userRightsReceiveError(const QString& error);
private:
    QNetworkAccessManager m_net;
    bool m_isValid;

    QString m_token;
    QString m_login;
    bool m_isAdmin;
};

#endif // SESSION_HPP
