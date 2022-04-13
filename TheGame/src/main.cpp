#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>


#include  "game.h"
#include "map/map.h"
#include "map/tile.h"
#include "entity/character.h"
#include "command.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    Game::getInstance();

    QQmlApplicationEngine engine;

    engine.addImportPath("qrc:/");

    engine.rootContext()->setContextProperty("game", &Game::getInstance());

    qmlRegisterUncreatableType<Map>("com.thegame.map", 1, 0, "Map", "Cannot create this object.");
    qmlRegisterUncreatableType<Character>("com.thegame.character", 1, 0, "Character", "Cannot create this object.");

    qmlRegisterType<Tile>("com.thegame.tile", 1, 0, "Tile");
    qmlRegisterType<Command>("com.thegame.command", 1, 0, "Command");

    qRegisterMetaType<Character*>("Character*");


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
