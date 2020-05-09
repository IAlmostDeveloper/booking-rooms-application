#include "RentsManager.hpp"
#include "Rentobject.hpp"
#include "../Auth/Authmanager.hpp"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

RentsManager::RentsManager(Session *session)
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

RentsModel *RentsManager::rentsModel()
{
    return m_rentsModel;
}

void RentsManager::setRentsModel(RentsModel *rentsModel)
{
    m_rentsModel = new RentsModel();
}

void RentsManager::setNewSession(const QString &token, const QString &login, bool isAdmin)
{
    m_currentSession = new Session(token, login, isAdmin);
}
