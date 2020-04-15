#ifndef AUTHMANAGER_HPP
#define AUTHMANAGER_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QString>

class AuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAuthProcessing READ isAuthProcessing WRITE setAuthProcessing NOTIFY authProcessingChanged)
    Q_PROPERTY(bool isRegProcessing READ isRegProcessing WRITE setRegProcessing NOTIFY regProcessingChanged)
public:
    explicit AuthManager(QObject *parent = nullptr);
    Q_INVOKABLE void auth(const QString& login, const QString& password);
    Q_INVOKABLE void reg(const QString& login, const QString& password);
    bool isAuthProcessing();
    void setAuthProcessing(bool value);
    bool isRegProcessing();
    void setRegProcessing(bool value);
    static int connectionPort();
    static void setConnectionPort(int port);
    static QString currentToken();
    static void setCurrentToken(const QString& token);

signals:
    void regFinished();
    void regFailed(const QString& error);
    void authFinished(const QString& token);
    void authFailed(const QString& error);
    void authProcessingChanged(bool value);
    void regProcessingChanged(bool value);

private slots:

private:
    QNetworkAccessManager m_net;
    bool m_isAuthProcessing;
    bool m_isRegProcessing;
    static int m_connectionPort;
    static QString m_currentToken;
};

#endif // AUTHMANAGER_HPP
