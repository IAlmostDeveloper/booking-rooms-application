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
                    QString hotel = roomRaw[1].remove("\"");
                    QString description = roomRaw[2].remove("\"").remove("]");
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
    qDebug() << str;
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit roomsDataReceiveError(reply->errorString());
        else
        {
            QString document = reply->readAll();
            document.remove("[").remove("]").remove("\"");
            qDebug() << document;
            if(document!="[]"){
                QStringList roomRaw = document.split(QRegExp(","), QString::SkipEmptyParts);
                int id = roomRaw[0].toInt();
                QString hotel = roomRaw[1];
                QString description = roomRaw[2];
                bool available = roomRaw[3].remove(" ")=="1" ? true : false;
                for(auto i:roomRaw)
                    qDebug() << i;
                m_roomsModel->append(new RoomObject(id, hotel, description, available));
            }
            emit roomsDataReceived();
        }
        reply->deleteLater();
    });
}

void RoomsManager::addRoomToDatabase(const QString& hotel, const QString &description, bool available)
{
    QUrl url(QString("http://localhost:8080/add/room"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["sessionToken"] = m_currentSession->token();
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

RoomsModel *RoomsManager::roomsModel()
{
    return m_roomsModel;
}

void RoomsManager::setRoomsModel(RoomsModel *roomsModel)
{
    m_roomsModel = new RoomsModel();
}

void RoomsManager::setNewSession(const QString &token, const QString &login, bool isAdmin)
{
    m_currentSession = new Session(token, login, isAdmin);
}
