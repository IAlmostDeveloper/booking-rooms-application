#include "Hotelsmodel.hpp"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QRegExp>
#include "Authmanager.hpp"
#include "Objects/Hotelobjdect.hpp"

HotelsModel::HotelsModel(QObject *parent) : QObject(parent)
{

}

void HotelsModel::getParsedHotelsList()
{
    QString str = QString("http://localhost:%1/hotels?token=%2")
            .arg(QString::number(AuthManager::connectionPort()), AuthManager::currentToken());
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit hotelsDataReceiveError(reply->errorString());
        else
        {
            QString document = reply->readAll();
            QList<QObject*> hotelsList = QList<QObject*>();
            QStringList raw = document.split(QRegExp("[[]"), QString::SkipEmptyParts);
            for(auto i : raw)
            {
                QStringList hotelRaw = i.split(QRegExp(","), QString::SkipEmptyParts);
                int id = hotelRaw[0].toInt();
                QString name = hotelRaw[1].remove("\"").remove(0,1);
                QString address = hotelRaw[2].remove("\"").remove("]");
                QString description = hotelRaw[3].remove("\"").remove("]");
                bool available = hotelRaw[4].remove(" ").remove("]")=="1" ? true : false;
                hotelsList.append(new HotelObject(id, name, address, description, available));
            }
            emit hotelsDataReceived(hotelsList);
        }
        reply->deleteLater();
    });
}

void HotelsModel::addHotelToDatabase(const QString& name, const QString& address,
                                     const QString& description, bool available)
{
    QUrl url(QString("http://localhost:%1/add/hotel").arg(AuthManager::connectionPort()));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["sessionToken"] = AuthManager::currentToken();
    body["name"] = name;
    body["address"] = address;
    body["description"] = description;
    body["available"] = available ? 1 : 0;
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit addHotelError(reply->errorString());
        else{
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            emit addHotelSuccess();
        }
        reply->deleteLater();
    });
}
