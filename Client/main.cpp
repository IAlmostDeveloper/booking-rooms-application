#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <cpp/App.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterUncreatableType<HotelObject>("Hotel", 1, 0, "HotelObject", "interface");
    qmlRegisterUncreatableType<RoomObject>("Room", 1, 0, "RoomObject", "interface");
    qmlRegisterType<HotelsModel>("Hotel", 1, 0, "HotelsModel");
    qmlRegisterType<RoomsModel>("Room", 1, 0, "RoomsModel");
    qmlRegisterSingletonType<App>("App", 1, 0, "App", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        static App* application = new App();
        return application;
    });

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
