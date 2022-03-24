#include "game.h"
#include <QDebug>

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

/*!
 * \brief End turn and initialization of properties for the next one.
 */
void Game::endTurn()
{
    nextPlayer();
}

/*!
 * \brief Select the next player turn.
 */
void Game::nextPlayer()
{
    if (roundPlayer == 2) {
        roundPlayer = 1;
        roundNum++;
        emit roundNumChanged();
    } else
        roundPlayer++;

    emit roundPlayerChanged();
}

/*!
 * \brief Handle of the click on the map.
 */
void Game::tileClicked(Tile *tile)
{
    Entity *entity = tile->getCharacter();

    if (entity == nullptr) {
        selectedEntity = nullptr;
        return;
    }

    if (entity->getPlayerOwner() != roundPlayer) {
        qDebug() << "Entity owner:" << entity->getPlayerOwner()
                 << " Round Player:" << roundPlayer;
        return;
    }

    selectedEntity = entity;

    if (dynamic_cast<Character*>(entity)) {
        Character *character = dynamic_cast<Character*>(entity);
        if (character->canAttack()) {
            qDebug() << "Can Attack";
        }

        if (character->canMove()) {
            qDebug() << "Can Move";
            //map->availableTileToMoveOn(character);
        }
    }
}
