#ifndef RENTSMANAGER_HPP
#define RENTSMANAGER_HPP

#include <QNetworkAccessManager>
#include "Rentsmodel.hpp"
#include "../Session.hpp"

class RentsManager : public QObject
{   
    Q_OBJECT
    Q_PROPERTY(RentsModel* rentsModel READ rentsModel WRITE setRentsModel NOTIFY rentsModelChanged)
public:
    explicit RentsManager(QObject* parent, Session* session = nullptr);
    Q_INVOKABLE void getUserRents(const QString& login);
    Q_INVOKABLE void getAllRents();
    Q_INVOKABLE void addUserRent(int roomId, const QString& user,
                                 const QString &fromDate, const QString &toDate);
    Q_INVOKABLE void addRent(int roomId, int userId,
                             const QString &fromDate, const QString &toDate);
    Q_INVOKABLE void editRent(int id,int roomId, int userId,
                              const QString &fromDate, const QString &toDate );
    Q_INVOKABLE void deleteRent(int id);

    RentsModel* rentsModel();
    void setRentsModel(RentsModel* rentsModel);
    void setNewSession(const QString& token, const QString& login, bool isAdmin);

signals:
    void rentsModelChanged();
    void rentsDataReceived();
    void rentsDataReceiveError(const QString& error);
    void addRentSuccess();
    void addRentError(const QString& error);
    void editRentSuccess();
    void editRentError(const QString& error);
    void deleteRentSuccess();
    void deleteRentError(const QString& error);

private:
    QNetworkAccessManager m_net;
    Session* m_currentSession;
    RentsModel* m_rentsModel;
};

#endif // RENTSMANAGER_HPP
