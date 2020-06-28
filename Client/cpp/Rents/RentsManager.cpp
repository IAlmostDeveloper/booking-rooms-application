#include "RentsManager.hpp"
#include "Rentobject.hpp"
#include "../Auth/Authmanager.hpp"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

RentsManager::RentsManager(QObject* parent, Session *session) : QObject(parent)
{
    m_currentSession = session;
    setRentsModel(new RentsModel());
}

void RentsManager::getUserRents(const QString &login)
{
    QString uri = "user-rents";
    QString user = QString("&user=%1").arg(login);

    QString str = QString("http://localhost:8080/%1?token=%2%3")
            .arg(uri, m_currentSession->token(), user);
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit rentsDataReceiveError(reply->errorString());
        else
        {
            m_rentsModel->clear();
            QString document = reply->readAll();
            document.remove("]");
            QStringList raw = document.split(QRegExp("[[]"), QString::SkipEmptyParts);
            if(raw.length()!=0)
                for(auto i : raw)
                {
                    QStringList roomRaw = i.split(QRegExp(","), QString::SkipEmptyParts);
                    int id = roomRaw[0].toInt();
                    int roomId = roomRaw[1].toInt();
                    int userId = roomRaw[2].toInt();
                    QString fromDate = roomRaw[3].remove("\"");
                    QString toDate = roomRaw[4].remove("\"");
                    m_rentsModel->append(new RentObject(id, roomId, userId, fromDate, toDate));
                }
            emit rentsDataReceived();
        }
        reply->deleteLater();
    });
}

void RentsManager::getAllRents()
{
    QString uri = "rents";

    QString str = QString("http://localhost:8080/rents?token=%1")
            .arg(m_currentSession->token());
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit rentsDataReceiveError(reply->errorString());
        else
        {
            m_rentsModel->clear();
            QString document = reply->readAll();
            document.remove("]");
            QStringList raw = document.split(QRegExp("[[]"), QString::SkipEmptyParts);
            if(raw.length()!=0)
                for(auto i : raw)
                {
                    QStringList roomRaw = i.split(QRegExp(","), QString::SkipEmptyParts);
                    int id = roomRaw[0].toInt();
                    int roomId = roomRaw[1].toInt();
                    int userId = roomRaw[2].toInt();
                    QString fromDate = roomRaw[3].remove("\"");
                    QString toDate = roomRaw[4].remove("\"");
                    m_rentsModel->append(new RentObject(id, roomId, userId, fromDate, toDate));
                }
            emit rentsDataReceived();
        }
        reply->deleteLater();
    });
}

void RentsManager::addUserRent(int roomId, const QString& user, const QString &fromDate, const QString &toDate)
{
    QUrl url(QString("http://localhost:8080/user-rent"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["token"] = m_currentSession->token();
    body["roomId"] = roomId;
    body["user"] = user;
    body["fromDate"] = fromDate;
    body["toDate"] = toDate;

    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit addRentError(reply->errorString());
        else{
            emit addRentSuccess();
        }
        reply->deleteLater();
    });
}

void RentsManager::addRent(int roomId, int userId, const QString &fromDate, const QString &toDate)
{
    QUrl url(QString("http://localhost:8080/rent"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["token"] = m_currentSession->token();
    body["roomId"] = roomId;
    body["userId"] = userId;
    body["fromDate"] = fromDate;
    body["toDate"] = toDate;

    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit addRentError(reply->errorString());
        else{
            emit addRentSuccess();
            getAllRents();
        }
        reply->deleteLater();
    });
}

void RentsManager::editRent(int id, int roomId, int userId, const QString &fromDate, const QString &toDate)
{
    QUrl url(QString("http://localhost:8080/rent"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["token"] = m_currentSession->token();
    body["id"] = id;
    body["roomId"] = roomId;
    body["userId"] = userId;
    body["fromDate"] = fromDate;
    body["toDate"] = toDate;

    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.put(request, bodyData);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit editRentError(reply->errorString());
        else{
            emit editRentSuccess();
            getAllRents();
        }
        reply->deleteLater();
    });
}

void RentsManager::deleteRent(int id)
{
    QUrl url(QString("http://localhost:8080/delete/rent"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["token"] = m_currentSession->token();
    body["id"] = id;
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit deleteRentError(reply->errorString());
        else{
            emit deleteRentSuccess();
            getAllRents();
        }
        reply->deleteLater();
    });
}

RentsModel *RentsManager::rentsModel()
{
    return m_rentsModel;
}

void RentsManager::setRentsModel(RentsModel *rentsModel)
{
    m_rentsModel = new RentsModel();
    emit rentsModelChanged();
}
