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
    Q_INVOKABLE void addHotelToDatabase(const QString& name, const QString& address,
                                        const QString& description, bool available);

signals:
    void hotelsDataReceived(const QList<QObject*>& hotelsData);
    void hotelsDataReceiveError(const QString& error);
    void addHotelSuccess();
    void addHotelError(const QString& error);
private:
    QList<QObject*> m_hotels;
    QNetworkAccessManager m_net;

};

#endif // HOTELSMODEL_HPP
