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


    moveCommand = new Command("qrc:/img/location.png", tr("Move"), this);
    moveCommand->setCanExecute(false);
    connect(moveCommand, &Command::executed, this, &Game::moveCommandClicked);
    commandBar.append(moveCommand);

    attackCommand = new Command("qrc:/img/slash.png", tr("Attack"), this);
    attackCommand->setCanExecute(false);
    connect(attackCommand, &Command::executed, this, &Game::attackCommandClicked);
    commandBar.append(attackCommand);

    healCommand = new Command("qrc:/img/heart.png", tr("Heal"), this);
    healCommand->setCanExecute(false);
    connect(healCommand, &Command::executed, this, &Game::endTurn);
    commandBar.append(healCommand);

    nextTurnCommand = new Command("qrc:/img/check.png", tr("End Turn"), this);
    nextTurnCommand->setCanExecute(true);
    connect(nextTurnCommand, &Command::executed, this, &Game::endTurn);
    commandBar.append(nextTurnCommand);
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

QQmlListProperty<Command> Game::getCommandBar()
{
    return QQmlListProperty<Command>(this, &commandBar);
}

/*!
 * \brief End turn and initialization of properties for the next one.
 */
void Game::endTurn()
{
    status = Idle;
    map->resetTiles();
    map->resetCharactersProperties();


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
 * \brief Move Command Clicked.
 */
void Game::moveCommandClicked()
{
    qDebug() << "Move command clicked!";
    if (selectedEntity) {
        status = Move;

        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        map->availableTileToMoveOn(character);
    }
}

/*!
 * \brief Game::attackCommandClicked
 */
void Game::attackCommandClicked() {
    qDebug() << "Attack command clicked!";
    if (selectedEntity) {
        status = Attack;

        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        map->availableCharacterToAttack(*character);
    }
}


/*!
 * \brief Handle of the click on the map.
 */
void Game::tileClicked(Tile *tile)
{

    switch (status) {
    case Idle:
        onIdleState(tile);
        break;
    case Move:
        onMoveState(tile);
        break;
    case Attack:
        break;
    default:
        break;
    }

    checkPermittedActions();
}

/*!
 * \brief Handling of idle state clicks on the map.
 */
void Game::onIdleState(Tile *tile)
{
    Entity *entity = tile->getCharacter();

    if (entity == nullptr) {
        selectedEntity = nullptr;
        map->resetTiles();
        return;
    }

    if (entity->getPlayerOwner() != roundPlayer) {
        qDebug() << "Entity owner:" << entity->getPlayerOwner()
                 << " Round Player:" << roundPlayer;
        return;
    }

    selectedEntity = entity;
}

/*!
 * \brief Handling of Move state clicks on the map.
 */
void Game::onMoveState(Tile *tile)
{
    if (tile->isFree()) {
        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        map->moveCharacterToTile(tile, character);
        map->resetTiles();
        status = Idle;
    }
}

/*!
 * \brief Game::checkPermittedActions
 */
void Game::checkPermittedActions()
{
    if (!selectedEntity) return;

    if (dynamic_cast<Character*>(selectedEntity.data())) {
        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        attackCommand->setCanExecute(false);
        if (character->canAttack()) {
            if (map->canAttackSomebody(*character)) {
                qDebug() << "Can Attack";
                attackCommand->setCanExecute(true);
            }
        }

        if (character->canMove()) {
            moveCommand->setCanExecute(true);
            qDebug() << "Can Move";
        } else {
            moveCommand->setCanExecute(false);
        }
    }
}
