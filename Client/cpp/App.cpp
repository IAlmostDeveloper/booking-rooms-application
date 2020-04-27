#include "App.hpp"



App::App(QObject *parent)
{
    setSession(new Session());
    setAuthManager(new AuthManager());
    setHotelsManager(new HotelsManager(m_session));
    QObject::connect(m_authManager, &AuthManager::authFinished, this, &App::createSession);
    QObject::connect(m_authManager, &AuthManager::authFinished, m_hotelsManager, &HotelsManager::setNewSession);
}

AuthManager* App::authManager()
{
    return m_authManager;
}

Session *App::session()
{
    return m_session;
}

HotelsManager *App::hotelsManager()
{
    return m_hotelsManager;
}

RoomsManager *App::roomsManager()
{
    return m_roomsManager;
}

RentsManager *App::rentsManager()
{
    return m_rentsManager;
}

void App::setAuthManager(AuthManager *authManager)
{
    m_authManager = authManager;
}

void App::createSession(const QString &token, const QString &login, bool isAdmin)
{
    qDebug() << "session created";
    m_session = new Session(token, login, isAdmin);
}

void App::setSession(Session *session)
{
    m_session = session;
}

void App::setHotelsManager(HotelsManager *hotelsManager)
{
    m_hotelsManager = hotelsManager;
}

void App::setRoomsManager(RoomsManager *roomsManager)
{
    m_roomsManager = roomsManager;
}

void App::setRentsManager(RentsManager *rentsManager)
{
    m_rentsManager = rentsManager;
}
