#include "Session.hpp"
#include <QDebug>
#include <QNetworkReply>


Session::Session()
{
    getUserRights();
}

Session::Session(const QString token, const QString &login, bool isAdmin)
{
    setToken(token);
    setLogin(login);
    setIsAdmin(isAdmin);
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
    qDebug() << Q_FUNC_INFO << m_isAdmin;
    return m_isAdmin;
}

void Session::setToken(const QString& token)
{
    m_token = token;
    emit tokenChanged();
}

void Session::setLogin(const QString& login)
{
    m_login = login;
    emit loginChanged();
}

void Session::setIsAdmin(bool isAdmin)
{
    m_isAdmin = isAdmin;
    emit isAdminChanged();
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

bool Session::isValid() const
{
    return m_isValid;
}

void Session::setIsValid(bool isValid)
{
    m_isValid = isValid;
}
