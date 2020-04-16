#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Models/Authmanager.hpp"
#include "Models/Hotelsmodel.hpp"
#include "Models/Roomsmodel.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qmlRegisterType<AuthManager>("AuthManager", 1, 0, "AuthManager");
    qmlRegisterType<HotelsModel>("HotelsModel", 1, 0, "HotelsModel");
    qmlRegisterType<RoomsModel>("RoomsModel", 1, 0, "RoomsModel");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
