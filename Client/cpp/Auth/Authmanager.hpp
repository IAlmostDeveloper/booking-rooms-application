#ifndef AUTHMANAGER_HPP
#define AUTHMANAGER_HPP

#include <QObject>
#include <QNetworkAccessManager>

class AuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAuthProcessing READ isAuthProcessing WRITE setAuthProcessing NOTIFY authProcessingChanged)
    Q_PROPERTY(bool isRegProcessing READ isRegProcessing WRITE setRegProcessing NOTIFY regProcessingChanged)
public:
    explicit AuthManager();
    virtual ~AuthManager();
    Q_INVOKABLE void auth(const QString& login, const QString& password);
    Q_INVOKABLE void reg(const QString& login, const QString& password, const QString& firstName,
                         const QString& lastName, const QString& passport="");
    bool isAuthProcessing();
    void setAuthProcessing(bool value);
    bool isRegProcessing();
    void setRegProcessing(bool value);

signals:
    void regFinished();
    void regFailed(const QString& error);
    void authFinished(const QString& token, const QString& login, bool isAdmin);
    void authFailed(const QString& error);
    void authProcessingChanged(bool value);
    void regProcessingChanged(bool value);

private:
    QNetworkAccessManager m_net;
    bool m_isAuthProcessing;
    bool m_isRegProcessing;
};

#endif // AUTHMANAGER_HPP
