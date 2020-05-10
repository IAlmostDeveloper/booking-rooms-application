#include "Session.hpp"
#include <QDebug>
#include <QNetworkReply>


Session::Session()
{
    m_token = "";
    m_login = "";
    getUserRights();
}

Session::Session(const QString token, const QString &login, bool isAdmin)
{
    m_token = token;
    m_login = login;
    m_isAdmin = isAdmin;
    getUserRights();
}

QString Session::token()
{
    return m_token;
}

QString Session::login()
{
    return m_login;
}

bool Session::isAdmin()
{
    return m_isAdmin;
}

void Session::setToken(const QString& token)
{
    m_token = token;
}

void Session::setLogin(const QString& login)
{
    m_login = login;
}

void Session::setIsAdmin(bool isAdmin)
{
    m_isAdmin = isAdmin;
}

void Session::getUserRights()
{
    QString str = QString("http://localhost:8080/user-rights?token=%1&user=%2")
            .arg(m_token, m_login);
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_net.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error()!=QNetworkReply::NoError)
            emit userRightsReceiveError(reply->errorString());
        else
        {
            QString rights = reply->readAll();
            rights.remove("\"");
            m_isAdmin = rights=="admin";
            emit userRightsReceiveSuccess(rights);
        }
        reply->deleteLater();
    });
}
