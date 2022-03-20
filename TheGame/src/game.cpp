#include "game.h"

/*!
 * \class Game
 * \details Singleton
 */

Game::Game(QObject *parent)
    : QObject{parent},
      roundNum(1),
      roundPlayer(1)
{
    map.reset(new Map(8,8));
}

Game & Game::getInstance()
{
    static Game instance;
    return instance;
}

int Game::getRoundNum()
{
    return roundNum;
}

int Game::getRoundPlayer()
{
    return roundPlayer;
}

Map *Game::getMap()
{
    return map.data();
}

void Game::nextPlayer()
{
    if (roundPlayer == 2) {
        roundPlayer = 1;
        roundNum++;
    } else
        roundPlayer++;
}
