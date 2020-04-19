#include "Roomsmodel.hpp"
#include "Authmanager.hpp"
#include <QNetworkReply>
#include "Objects/Roomobject.hpp"
#include <QJsonDocument>
#include <QJsonObject>

RoomsModel::RoomsModel(QObject *parent) : QObject(parent)
{

}

void RoomsModel::getParsedRoomsList(bool isOnlyAvailable, const QString& hotel)
{
    QString port = QString::number(AuthManager::connectionPort());
    QString token = AuthManager::currentToken();
    QString uri = !isOnlyAvailable && hotel=="" ? "rooms" :
                   isOnlyAvailable && hotel=="" ? "available-rooms" :
                  !isOnlyAvailable && hotel!="" ? "hotel-rooms" :
                   isOnlyAvailable && hotel!="" ? "hotel-available-rooms" : "";
    QString hotelName = hotel!="" ? QString("&hotel=%1").arg(hotel) : "";

    QString str = QString("http://localhost:%1/%2?token=%3%4")
            .arg(port, uri, token, hotelName);
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit roomsDataReceiveError(reply->errorString());
        else
        {
            QString document = reply->readAll();
            document.remove("]");
            QList<QObject*> roomsList = QList<QObject*>();
            QStringList raw = document.split(QRegExp("[[]"), QString::SkipEmptyParts);
            if(raw.length()!=0)
                for(auto i : raw)
                {
                    QStringList roomRaw = i.split(QRegExp(","), QString::SkipEmptyParts);
                    int id = roomRaw[0].toInt();
                    QString hotel = roomRaw[1].remove("\"");
                    QString description = roomRaw[2].remove("\"").remove("]");
                    bool available = roomRaw[3].remove(" ").remove("]")=="1" ? true : false;
                    roomsList.append(new RoomObject(id, hotel, description, available));
                }
            emit roomsDataReceived(roomsList);
        }
        reply->deleteLater();
    });
}

void RoomsModel::addRoomToDatabase(const QString& hotel, const QString &description, bool available)
{
    QUrl url(QString("http://localhost:%1/add/room").arg(AuthManager::connectionPort()));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["sessionToken"] = AuthManager::currentToken();
    body["hotelId"] = hotel;
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
