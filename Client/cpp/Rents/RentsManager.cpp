#include "RentsManager.hpp"
#include "Rentobject.hpp"
#include "../Auth/Authmanager.hpp"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

RentsManager::RentsManager(Session *session)
{
    m_currentSession = session;
}

void RentsManager::getUserRents(const QString &login)
{
    QString port = QString::number(8080);
    QString uri = "user-rents";
    QString user = QString("&user=%1").arg(login);

    QString str = QString("http://localhost:%1/%2?token=%3%4")
            .arg(port, uri, "123", user);
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit rentsDataReceiveError(reply->errorString());
        else
        {
            QString document = reply->readAll();
            document.remove("]");
            QList<QObject*> roomsList = QList<QObject*>();
            QStringList raw = document.split(QRegExp("[[]"), QString::SkipEmptyParts);
            qDebug() << raw;
            if(raw.length()!=0)
                for(auto i : raw)
                {
                    qDebug() << i;
                    QStringList roomRaw = i.split(QRegExp(","), QString::SkipEmptyParts);
                    int id = roomRaw[0].toInt();
                    int roomId = roomRaw[1].toInt();
                    int userId = roomRaw[2].toInt();
                    QString fromDate = roomRaw[3].remove("\"");
                    QString toDate = roomRaw[4].remove("\"");
                    roomsList.append(new RentObject(id, roomId, userId, fromDate, toDate));
                }
            emit rentsDataReceived(roomsList);
        }
        reply->deleteLater();
    });
}
