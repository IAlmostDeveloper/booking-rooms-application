#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Hotelsmodel.hpp"
#include "Authmanager.hpp"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qmlRegisterType<AuthManager>("io.qt.auth.manager", 1, 0, "AuthManager");
    qmlRegisterType<HotelsModel>("io.qt.models.hotels", 1, 0, "HotelsModel");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
