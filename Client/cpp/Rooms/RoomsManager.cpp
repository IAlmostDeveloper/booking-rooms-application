#include "RoomsManager.hpp"
#include "../Auth/Authmanager.hpp"
#include <QNetworkReply>
#include "Roomobject.hpp"
#include <QJsonDocument>
#include <QJsonObject>

RoomsManager::RoomsManager(Session *session)
{
    m_currentSession = session;
    setRoomsModel(new RoomsModel());
}

RoomsManager::~RoomsManager()
{
    delete m_roomsModel;
    delete m_currentSession;
    m_net.deleteLater();
}

void RoomsManager::getParsedRoomsList(bool isOnlyAvailable, const QString& hotel)
{
    QString uri = !isOnlyAvailable && hotel=="" ? "rooms" :
                   isOnlyAvailable && hotel=="" ? "available-rooms" :
                  !isOnlyAvailable && hotel!="" ? "hotel-rooms" :
                   isOnlyAvailable && hotel!="" ? "hotel-available-rooms" : "";
    QString hotelName = hotel!="" ? QString("&hotel=%1").arg(hotel) : "";

    QString str = QString("http://localhost:8080/%1?token=%2%3")
            .arg(uri, m_currentSession->token(), hotelName);
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit roomsDataReceiveError(reply->errorString());
        else
        {
            m_roomsModel->clear();
            QString document = reply->readAll();
            document.remove("]");
            QStringList raw = document.split(QRegExp("[[]"), QString::SkipEmptyParts);
            if(raw.length()!=0)
                for(auto i : raw)
                {
                    QStringList roomRaw = i.split(QRegExp(","), QString::SkipEmptyParts);
                    int id = roomRaw[0].toInt();
                    QString hotel = roomRaw[1].remove("\"").remove(0, 1);
                    QString description = roomRaw[2].remove("\"").remove("]").remove(0, 1);
                    bool available = roomRaw[3].remove(" ").remove("]")=="1" ? true : false;
                    m_roomsModel->append(new RoomObject(id, hotel, description, available));
                }
            emit roomsDataReceived();
        }
        reply->deleteLater();
    });
}

void RoomsManager::getRoom(int id)
{
    QString str = QString("http://localhost:8080/room?token=%1&room=%2")
            .arg(m_currentSession->token(), QString::number(id));
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit roomDataReceiveError(reply->errorString());
        else
        {
            QString document = reply->readAll();
            document.remove("[")
                    .remove("]")
                    .remove("\"");
            if(document!="[]"){
                QStringList roomRaw = document.split(QRegExp(","), QString::SkipEmptyParts);
                int id = roomRaw[0].toInt();
                QString hotel = roomRaw[1];
                QString description = roomRaw[2];
                bool available = roomRaw[3].remove(" ")=="1" ? true : false;
                emit roomDataReceived(id, hotel, description, available);
            }       
        }
        reply->deleteLater();
    });
}

void RoomsManager::addRoomToDatabase(const QString& hotel, const QString &description, bool available)
{
    QUrl url(QString("http://localhost:8080/room"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["token"] = m_currentSession->token();
    body["hotel"] = hotel;
    body["description"] = description;
    body["available"] = available ? 1 : 0;
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit addRoomError(reply->errorString());
        else
        {
            emit addRoomSuccess();
            getParsedRoomsList(false);
        }
        reply->deleteLater();
    });
}

void RoomsManager::editRoom(int id, const QString &hotel, const QString &description, bool available)
{
    QUrl url(QString("http://localhost:8080/room"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["token"] = m_currentSession->token();
    body["id"] = id;
    body["hotel"] = hotel;
    body["description"] = description;
    body["available"] = available ? 1 : 0;
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.put(request, bodyData);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit editRoomError(reply->errorString());
        else
        {
            emit editRoomSuccess();
            getParsedRoomsList(false);
        }
        reply->deleteLater();
    });
}

void RoomsManager::deleteRoom(int id)
{
    QUrl url(QString("http://localhost:8080/deleste/room"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["token"] = m_currentSession->token();
    body["id"] = id;
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit deleteRoomError(reply->errorString());
        else
        {
            emit deleteRoomSuccess();
            getParsedRoomsList(false);
        }
        reply->deleteLater();
    });
}

void RoomsManager::getRoomBookedDays(int roomId)
{
    QString str = QString("http://localhost:8080/room-rents?token=%1&room=%2")
            .arg(m_currentSession->token(), QString::number(roomId));
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit roomBookedDaysReceiveError(reply->errorString());
        else
        {
            QStringList bookedDays;
            QString document = reply->readAll();
            document.remove("[")
                    .remove("]")
                    .remove("\"")
                    .remove(" ")
                    .remove("(")
                    .remove(")");
            QStringList parsed = document.split(",", Qt::SkipEmptyParts);
            for(int i=3;i<parsed.length();i+=5)
                bookedDays.append(parsed[i]);
            emit roomBookedDaysReceiveSuccess(bookedDays);
        }
        reply->deleteLater();
    });
}

RoomsModel *RoomsManager::roomsModel()
{
    return m_roomsModel;
}

void RoomsManager::setRoomsModel(RoomsModel *roomsModel)
{
    m_roomsModel = new RoomsModel();
    emit roomsModelChanged();
}
