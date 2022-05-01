#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>


#include  "game.h"
#include "map/map.h"
#include "map/tile.h"
#include "entity/dynamicentity.h"
#include "entity/character.h"
#include "entity/castle.h"
#include "command.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    game::Game::getInstance();

    QQmlApplicationEngine engine;

    engine.addImportPath("qrc:/");

    engine.rootContext()->setContextProperty("game", &game::Game::getInstance());

    qmlRegisterUncreatableType<game::map::Map>("com.thegame.map", 1, 0, "Map", "Cannot create this object.");
    qmlRegisterUncreatableType<game::entity::Character>("com.thegame.character", 1, 0, "Character", "Cannot create this object.");
    qmlRegisterUncreatableType<game::entity::Castle>("com.thegame.castle", 1, 0, "Castle", "Cannot create this object.");

    qmlRegisterType<game::map::Tile>("com.thegame.tile", 1, 0, "Tile");
    qmlRegisterType<game::Command>("com.thegame.command", 1, 0, "Command");

    qRegisterMetaType<game::entity::Character*>("Character*");


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
