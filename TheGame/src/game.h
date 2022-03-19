#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "map/map.h"

class Game : public QObject
{
    Q_OBJECT
public:
    static Game& getInstance();

    int getRoundNum();
    int getRoundPlayer();

    void nextPlayer();

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
private:
    Game(QObject *parent = nullptr);

    int roundNum;
    int roundPlayer;

    /* I used smart pointers only for learning purposes.
     * It should be fine and easier to use the parent-child
     * relations offered by Qt. */
    QScopedPointer<Map> map;

};

#endif // GAME_H
