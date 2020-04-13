#include "Hotelsmodel.hpp"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QRegExp>
#include "Authmanager.hpp"
#include "Hotelobjdect.hpp"

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
            qDebug() << reply->errorString();
        else{
            QString document = reply->readAll();
            QList<QObject*> hotelsList = QList<QObject*>();
            QStringList raw = document.split(QRegExp("[[]"), QString::SkipEmptyParts);
            qDebug() << raw;
            qDebug() << raw.length();
            for(auto i : raw){
                QStringList hotelRaw = i.split(QRegExp(","), QString::SkipEmptyParts);
                qDebug()<<hotelRaw;
                int id = hotelRaw[0].toInt();
                QString name = hotelRaw[1].replace("\"", "");
                bool available = hotelRaw[2]=="1" ? true : false;
                QString address = hotelRaw[3].replace("\"", "");
                hotelsList.append(new HotelObject(name, address, id, available));
            }
            for(auto i: hotelsList){
                qDebug() << i;
            }
            emit hotelsDataReceived(hotelsList);
        }
        reply->deleteLater();
    });
}
