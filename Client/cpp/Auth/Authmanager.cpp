#include "Authmanager.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>
#include <QString>

AuthManager::AuthManager(QObject* parent) : QObject(parent)
{
    m_isAuthProcessing = false;
    m_isRegProcessing = false;
}

AuthManager::~AuthManager()
{
    m_net.deleteLater();
}

void AuthManager::auth(const QString &login, const QString &password){
    setAuthProcessing(true);
    QUrl url("http://localhost:8080/auth");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["login"] = login;
    body["password"] = password;
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply, login](){
        if(reply->error()!=QNetworkReply::NoError)
            emit authFailed(reply->errorString());
        else{
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            emit authFinished(document["token"].toString(),
                    login, document["isAdmin"].toBool());
        }
        reply->deleteLater();
        setAuthProcessing(false);
    });
}

void AuthManager::reg(const QString& login, const QString& password, const QString& firstName,
                      const QString& lastName, const QString& passport)
{
    setRegProcessing(true);
    QUrl url("http://localhost:8080/register");
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
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
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
