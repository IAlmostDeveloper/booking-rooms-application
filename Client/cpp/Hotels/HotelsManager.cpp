#include "HotelsManager.hpp"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QRegExp>

HotelsManager::HotelsManager(Session *session)
{
    m_currentSession = session;
    setHotelsModel(new HotelsModel());
}

void HotelsManager::getParsedHotelsList()
{
    QString str = QString("http://localhost:8080/hotels?token=%1")
            .arg(m_currentSession->token());
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit hotelsDataReceiveError(reply->errorString());
        else
        {
            m_hotelsModel->clear();
            QString document = reply->readAll();
            QStringList raw = document.split(QRegExp("[[]"), QString::SkipEmptyParts);
            if(raw.length()!=0)
                for(auto i : raw)
                {
                    QStringList hotelRaw = i.split(QRegExp(","), QString::SkipEmptyParts);
                    int id = hotelRaw[0].toInt();
                    QString name = hotelRaw[1].remove("\"").remove(0,1);
                    QString address = hotelRaw[2].remove("\"").remove("]");
                    QString description = hotelRaw[3].remove("\"").remove("]");
                    bool available = hotelRaw[4].remove(" ").remove("]")=="1" ? true : false;
                    m_hotelsModel->append(new HotelObject(id, name, address, description, available));
                }
            emit hotelsDataReceived();
        }
        reply->deleteLater();
    });
}

void HotelsManager::addHotelToDatabase(const QString& name, const QString& address,
                                     const QString& description, bool available)
{
    QUrl url(QString("http://localhost:8080/add/hotel"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["sessionToken"] = m_currentSession->token();
    body["name"] = name;
    body["address"] = address;
    body["description"] = description;
    body["available"] = available ? 1 : 0;
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit addHotelError(reply->errorString());
        else{
            emit addHotelSuccess();
            getParsedHotelsList();
        }
        reply->deleteLater();
    });
}

void HotelsManager::deleteHotel(int id)
{
    QUrl url(QString("http://localhost:8080/delete/hotel"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["sessionToken"] = m_currentSession->token();
    body["id"] = id;
    QByteArray bodyData = QJsonDocument(body).toJson();
    QNetworkReply *reply = m_net.post(request, bodyData);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit deleteHotelError(reply->errorString());
        else{
            emit deleteHotelSuccess();
            getParsedHotelsList();
        }
        reply->deleteLater();
    });
}

HotelsModel *HotelsManager::hotelsModel()
{
    return m_hotelsModel;
}

void HotelsManager::setHotelsModel(HotelsModel *hotelsModel)
{
    m_hotelsModel = hotelsModel;
    emit hotelsModelChanged();
}
