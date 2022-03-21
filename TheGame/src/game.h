#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "map/map.h"

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY (Map *map_ui READ getMap CONSTANT)
    Q_PROPERTY(int roundNum READ getRoundNum NOTIFY roundNumChanged)
    Q_PROPERTY(int roundPlayer READ getRoundPlayer NOTIFY roundPlayerChanged)
public:
    static Game& getInstance();

    int getRoundNum();    
    int getRoundPlayer();
    Map *getMap();

    void nextPlayer();

    Q_INVOKABLE void setSelectedEntity(Entity *entity);

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

signals:
    void roundNumChanged();
    void roundPlayerChanged();

private:
    Game(QObject *parent = nullptr);

    int roundNum;
    int roundPlayer;

    /* I used smart pointers only for learning purposes.
     * It should be fine and easier to use the parent-child
     * relations offered by Qt. */
    QScopedPointer<Map> map;

    QPointer<Entity> selectedEntity {nullptr};
};

#endif // GAME_H
