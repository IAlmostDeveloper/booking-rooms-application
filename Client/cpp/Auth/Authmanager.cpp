#include "Authmanager.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>
#include <QString>

AuthManager::AuthManager()
{
    m_isAuthProcessing = false;
    m_isRegProcessing = false;
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

    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        qDebug() << "lambda";
        if(reply->error()!=QNetworkReply::NoError){
            qDebug() << reply->errorString();
            emit authFailed(reply->errorString());
        }
        else{
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            emit authFinished(document["token"].toString(),
                    document["login"].toString(),document["isAdmin"].toBool());
            qDebug() << "signal emit success";
        }
        reply->deleteLater();
        setAuthProcessing(false);
    });
}

void AuthManager::reg(const QString& login, const QString& password, const QString& firstName,
                      const QString& lastName, const QString& passport)
{
    setRegProcessing(true);
    QUrl url(QString("http://localhost:%1/register").arg(8080));
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
