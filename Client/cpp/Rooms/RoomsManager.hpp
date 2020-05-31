#ifndef ROOMSMANAGER_HPP
#define ROOMSMANAGER_HPP

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
    Q_INVOKABLE void getRoom(int id);
    Q_INVOKABLE void addRoomToDatabase(const QString& hotel,
                                       const QString& description, bool available);
    Q_INVOKABLE void deleteRoom(int id);
    Q_INVOKABLE void getRoomBookedDays(int roomId);
    RoomsModel* roomsModel();
    void setRoomsModel(RoomsModel* roomsModel);
    void setNewSession(const QString& token, const QString& login, bool isAdmin);

signals:
    void roomsModelChanged();
    void roomDataReceived(int id, const QString& hotel, const QString& description, bool available);
    void roomDataReceiveError(const QString& error);
    void roomsDataReceived();
    void roomsDataReceiveError(const QString& error);
    void roomBookedDaysReceiveError(const QString& error);
    void roomBookedDaysReceiveSuccess(QStringList bookedDays);
    void addRoomSuccess();
    void addRoomError(const QString& error);
    void deleteRoomSuccess();
    void deleteRoomError(const QString& error);

private:
    QNetworkAccessManager m_net;
    Session* m_currentSession;
    RoomsModel* m_roomsModel;
};

#endif // ROOMSMANAGER_HPP
