#include "App.hpp"



App::App(QObject *parent)
{
    setSession(new Session());
    setAuthManager(new AuthManager());
    setHotelsManager(new HotelsManager(m_session));
    setRoomsManager(new RoomsManager(m_session));
    setRentsManager(new RentsManager(m_session));

    QObject::connect(m_authManager, &AuthManager::authFinished, this, &App::initSession);
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
    emit authManagerChanged();
}

void App::initSession(const QString &token, const QString &login, bool isAdmin)
{
    m_session->setToken(token);
    m_session->setLogin(login);
    m_session->setIsAdmin(isAdmin);
    m_session->setIsValid(true);
    emit sessionChanged();

}

void App::invalidateSession()
{
    m_session->setToken("");
    m_session->setLogin("");
    m_session->setIsAdmin(false);
    m_session->setIsValid(false);
    emit sessionChanged();
}

void App::setSession(Session *session)
{
    m_session = session;
    emit sessionChanged();
}

void App::setHotelsManager(HotelsManager *hotelsManager)
{
    m_hotelsManager = hotelsManager;
    emit hotelsManagerChanged();
}

void App::setRoomsManager(RoomsManager *roomsManager)
{
    m_roomsManager = roomsManager;
    emit roomsManagerChanged();
}

void App::setRentsManager(RentsManager *rentsManager)
{
    m_rentsManager = rentsManager;
    emit rentsManagerChanged();
}
