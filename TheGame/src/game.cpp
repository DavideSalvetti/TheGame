#include "game.h"

/*!
 * \class Game
 * \details Singleton
 */

Game::Game(QObject *parent)
    : QObject{parent}
{

}

Game & Game::getInstance()
{
    static Game instance;
    return instance;
}
