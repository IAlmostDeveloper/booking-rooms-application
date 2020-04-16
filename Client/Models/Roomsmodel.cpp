#include "Roomsmodel.hpp"
#include "Authmanager.hpp"
#include <QNetworkReply>
#include "Objects/Roomobject.hpp"
#include <QJsonDocument>
#include <QJsonObject>

RoomsModel::RoomsModel(QObject *parent) : QObject(parent)
{

}

void RoomsModel::getParsedRoomsList(bool isOnlyAvailable, int hotelId)
{
    QString port = QString::number(AuthManager::connectionPort());
    QString token = AuthManager::currentToken();
    QString uri = !isOnlyAvailable && hotelId==0 ? "rooms" :
                   isOnlyAvailable && hotelId==0 ? "available-rooms" :
                  !isOnlyAvailable && hotelId!=0 ? "hotel-rooms" :
                   isOnlyAvailable && hotelId!=0 ? "hotel-available-rooms" : "";
    QString hotel = hotelId != 0 ? QString("&hotel=%1").arg(hotelId) : "";

    QString str = QString("http://localhost:%1/%2?token=%3%4")
            .arg(port, uri, token, hotel);
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit roomsDataReceiveError(reply->errorString());
        else
        {
            QString document = reply->readAll();
            QList<QObject*> roomsList = QList<QObject*>();
            QStringList raw = document.split(QRegExp("[[]"), QString::SkipEmptyParts);
            qDebug() << raw;
            for(auto i : raw)
            {
                QStringList roomRaw = i.split(QRegExp(","), QString::SkipEmptyParts);
                qDebug() << roomRaw;
                int id = roomRaw[0].toInt();
                int hotelId = roomRaw[1].toInt();
                QString description = roomRaw[2].replace("\"", "").replace("]", "");
                bool available = roomRaw[3].remove(" ").remove("]")=="1" ? true : false;
                roomsList.append(new RoomObject(id, hotelId, description, available));
            }
            emit roomsDataReceived(roomsList);
        }
        reply->deleteLater();
    });
}

void RoomsModel::addRoomToDatabase(int hotelId, const QString &description, bool available)
{
    QUrl url(QString("http://localhost:%1/add/room").arg(AuthManager::connectionPort()));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["sessionToken"] = AuthManager::currentToken();
    body["hotelId"] = hotelId;
    body["description"] = description;
    body["available"] = available ? 1 : 0;
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit addRoomError(reply->errorString());
        else{
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            emit addRoomSuccess();
        }
        reply->deleteLater();
    });
}
