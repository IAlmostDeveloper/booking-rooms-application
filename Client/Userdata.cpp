#include "Userdata.hpp"
#include "Models/Authmanager.hpp"

UserData::UserData(QObject *parent) : QObject(parent)
{

}

QString UserData::getCurrentToken()
{
    return AuthManager::currentToken();
}

QString UserData::getCurrentLogin()
{
    return AuthManager::currentLogin();
}
