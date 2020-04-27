#ifndef ROOMSMANAGER_HPP
#define ROOMSMANAGER_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include "Roomsmodel.hpp"
#include "../Session.hpp"

class RoomsManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RoomsModel* roomsModel READ roomsModel WRITE setRoomsModel NOTIFY roomsModelChanged)
public:
    explicit RoomsManager(Session* session = nullptr);
    Q_INVOKABLE void getParsedRoomsList(bool isOnlyAvailable, const QString& hotel = "");
    Q_INVOKABLE void addRoomToDatabase(const QString& hotel,
                                       const QString& description, bool available);
    RoomsModel* roomsModel();
    void setRoomsModel(RoomsModel* roomsModel);
    void setNewSession(const QString& token, const QString& login, bool isAdmin);

signals:
    void roomsModelChanged();
    void roomsDataReceived();
    void roomsDataReceiveError(const QString& error);
    void addRoomSuccess();
    void addRoomError(const QString& error);
private:
    QNetworkAccessManager m_net;
    Session* m_currentSession;
    RoomsModel* m_roomsModel;
};

#endif // ROOMSMANAGER_HPP
