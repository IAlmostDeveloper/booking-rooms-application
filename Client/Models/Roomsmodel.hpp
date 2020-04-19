#ifndef ROOMSMODEL_HPP
#define ROOMSMODEL_HPP

#include <QObject>
#include <QNetworkAccessManager>

class RoomsModel : public QObject
{
    Q_OBJECT
public:
    explicit RoomsModel(QObject *parent = nullptr);
    Q_INVOKABLE void getParsedRoomsList(bool isOnlyAvailable, const QString& hotel = "");
    Q_INVOKABLE void addRoomToDatabase(const QString& hotel,
                                       const QString& description, bool available);

signals:
    void roomsDataReceived(const QList<QObject*>& roomsData);
    void roomsDataReceiveError(const QString& error);
    void addRoomSuccess();
    void addRoomError(const QString& error);
private:
    QList<QObject*> m_rooms;
    QNetworkAccessManager m_net;
};

#endif // ROOMSMODEL_HPP
