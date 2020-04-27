#ifndef RENTSMANAGER_HPP
#define RENTSMANAGER_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include "Rentsmodel.hpp"
#include "../Session.hpp"

class RentsManager : public QObject
{
    Q_OBJECT
public:
    explicit RentsManager(Session* session = nullptr);
    Q_INVOKABLE void getUserRents(const QString& login);

signals:
    void rentsDataReceived(const QList<QObject*>& rentsData);
    void rentsDataReceiveError(const QString& error);
    void addRentSuccess();
    void addRentError(const QString& error);
private:
    QNetworkAccessManager m_net;
    Session* m_currentSession;
    RentsModel* m_rentsModel;
};

#endif // RENTSMANAGER_HPP
