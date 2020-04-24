#include "Rentsmodel.hpp"
#include "../Objects/Rentobject.hpp"
#include "Authmanager.hpp"
#include <QNetworkReply>
#include "Objects/Roomobject.hpp"
#include <QJsonDocument>
#include <QJsonObject>

RentsModel::RentsModel(QObject *parent) : QObject(parent)
{

}

void RentsModel::getUserRents(const QString &login)
{
    QString port = QString::number(AuthManager::connectionPort());
    QString token = AuthManager::currentToken();
    QString uri = "user-rents";
    QString user = QString("&user=%1").arg(login);

    QString str = QString("http://localhost:%1/%2?token=%3%4")
            .arg(port, uri, token, user);
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    connect(reply, &QNetworkReply::finished, [this, reply](){
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
                    QString fromDate = roomRaw[3];
                    QString toDate = roomRaw[4];
                    roomsList.append(new RentObject(id, roomId, userId, fromDate, toDate));
                }
            emit rentsDataReceived(roomsList);
        }
        reply->deleteLater();
    });
}
