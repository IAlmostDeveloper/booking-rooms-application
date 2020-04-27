#include "Session.hpp"
#include <QDebug>


Session::Session()
{
    m_currentToken = "";
    m_currentLogin = "";
    m_isAdmin = false;
}

Session::Session(const QString token, const QString &login, bool isAdmin)
{
    qDebug() << "Session constructor";
    m_currentToken = token;
    m_currentLogin = login;
    m_isAdmin = isAdmin;
}

QString Session::currentToken()
{
    return m_currentToken;
}

QString Session::currentLogin()
{
    return m_currentLogin;
}

bool Session::isAdmin()
{
    return m_isAdmin;
}
