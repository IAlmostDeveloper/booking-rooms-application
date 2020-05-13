#ifndef APP_HPP
#define APP_HPP

#include <QObject>
#include "Auth/Authmanager.hpp"
#include "Hotels/HotelsManager.hpp"
#include "Rooms/RoomsManager.hpp"
#include "Rents/RentsManager.hpp"
#include "Session.hpp"

class App : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AuthManager* authManager READ authManager WRITE setAuthManager NOTIFY authManagerChanged)
    Q_PROPERTY(Session* session READ session WRITE setSession NOTIFY sessionChanged)
    Q_PROPERTY(HotelsManager* hotelsManager READ hotelsManager WRITE setHotelsManager NOTIFY hotelsManagerChanged)
    Q_PROPERTY(RoomsManager* roomsManager READ roomsManager WRITE setRoomsManager NOTIFY roomsManagerChanged)
    Q_PROPERTY(RentsManager* rentsManager READ rentsManager WRITE setRentsManager NOTIFY rentsManagerChanged)
public:
    App(QObject *parent = nullptr);

    AuthManager* authManager();
    Session* session();
    HotelsManager* hotelsManager();
    RoomsManager* roomsManager();
    RentsManager* rentsManager();

    void setAuthManager(AuthManager* authManager);
    void setSession(Session* session);
    void setHotelsManager(HotelsManager* hotelsManager);
    void setRoomsManager(RoomsManager* roomsManager);
    void setRentsManager(RentsManager* rentsManager);

    Q_INVOKABLE void initSession(const QString& token, const QString& login, bool isAdmin);
    Q_INVOKABLE void invalidateSession();
signals:
    void authManagerChanged();
    void sessionChanged();
    void hotelsManagerChanged();
    void roomsManagerChanged();
    void rentsManagerChanged();

private:
    AuthManager* m_authManager;
    Session* m_session;
    HotelsManager* m_hotelsManager;
    RoomsManager* m_roomsManager;
    RentsManager* m_rentsManager;
};

#endif // APP_HPP
