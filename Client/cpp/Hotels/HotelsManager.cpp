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
            .arg(m_currentSession->currentToken());
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
    QUrl url(QString("http://localhost:%1/add/hotel").arg(8080));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["sessionToken"] = 123;
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
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            emit addHotelSuccess();
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
}

void HotelsManager::setNewSession(const QString &token, const QString &login, bool isAdmin)
{
    m_currentSession = new Session(token, login, isAdmin);
}
