#ifndef HOTELSMODEL_HPP
#define HOTELSMODEL_HPP

#include <QObject>
#include <QNetworkAccessManager>

class HotelsModel : public QObject
{
    Q_OBJECT
public:
    explicit HotelsModel(QObject *parent = nullptr);
    Q_INVOKABLE void getParsedHotelsList();

signals:
    void hotelsDataReceived(const QList<QObject*>& hotelsData);
private:
    QList<QObject*> m_hotels;
    QNetworkAccessManager m_net;

};

#endif // HOTELSMODEL_HPP
