#include "Session.hpp"
#include <QDebug>


Session::Session()
{
    m_token = "";
    m_login = "";
    m_isAdmin = false;
}

Session::Session(const QString token, const QString &login, bool isAdmin)
{
    m_token = token;
    m_login = login;
    m_isAdmin = isAdmin;
}

QString Session::token()
{
    return m_token;
}

QString Session::login()
{
    return m_login;
}

void Session::setToken(const QString& token)
{
    m_token = token;
}

void Session::setLogin(const QString& login)
{
    m_login = login;
}

bool Session::isAdmin()
{
    return m_isAdmin;
}
