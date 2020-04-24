#include "Authmanager.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>
#include <QString>

AuthManager::AuthManager(QObject *parent) : QObject(parent)
{
    m_isAuthProcessing = false;
    m_isRegProcessing = false;
}

int AuthManager::m_connectionPort = 8080;
QString AuthManager::m_currentToken;
QString AuthManager::m_currentLogin;

void AuthManager::auth(const QString &login, const QString &password){
    setAuthProcessing(true);
    QUrl url(QString("http://localhost:%1/auth").arg(AuthManager::connectionPort()));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["login"] = login;
    body["password"] = password;
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    connect(reply, &QNetworkReply::finished, [this, reply, login](){
        if(reply->error()!=QNetworkReply::NoError)
            emit authFailed(reply->errorString());
        else{
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonValue tokenValue = document["token"];
            AuthManager::setCurrentToken(tokenValue.toString());
            AuthManager::setCurrentLogin(login);
            emit authFinished(tokenValue.toString());
        }
        reply->deleteLater();
        setAuthProcessing(false);
    });
}

void AuthManager::reg(const QString& login, const QString& password, const QString& firstName,
                      const QString& lastName, const QString& passport)
{
    setRegProcessing(true);
    QUrl url(QString("http://localhost:%1/register").arg(AuthManager::connectionPort()));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["login"] = login;
    body["password"] = password;
    body["firstName"] = firstName;
    body["lastName"] = lastName;
    body["passport"] = passport;
    body["rights"] = "none";
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);
    connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit regFailed(reply->errorString());
        else
            emit regFinished();
        reply->deleteLater();
        setRegProcessing(false);
    });
}

bool AuthManager::isAuthProcessing()
{
    return m_isAuthProcessing;
}

void AuthManager::setAuthProcessing(bool value)
{
    if(m_isAuthProcessing==value)
        return;
    m_isAuthProcessing=value;
    emit authProcessingChanged(value);
}

bool AuthManager::isRegProcessing()
{
    return m_isRegProcessing;
}

void AuthManager::setRegProcessing(bool value)
{
    if(m_isRegProcessing==value)
        return;
    m_isRegProcessing=value;
    emit regProcessingChanged(value);
}

int AuthManager::connectionPort()
{
    return AuthManager::m_connectionPort;
}

void AuthManager::setConnectionPort(int port)
{
    AuthManager::m_connectionPort = port;
}

QString AuthManager::currentToken()
{
    return AuthManager::m_currentToken;
}

void AuthManager::setCurrentToken(const QString &token)
{
    AuthManager::m_currentToken = token;
}

QString AuthManager::currentLogin()
{
    return AuthManager::m_currentLogin;
}

void AuthManager::setCurrentLogin(const QString &login)
{
    AuthManager::m_currentLogin = login;
}
