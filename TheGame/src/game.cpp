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


    moveCommand = new Command("qrc:/img/location.png", tr("Move"), this);
    moveCommand->setCanExecute(false);
    connect(moveCommand, &Command::executed, this, &Game::moveCommandClicked);
    commandBar.append(moveCommand);

    attackCommand = new Command("qrc:/img/slash.png", tr("Attack"), this);
    attackCommand->setCanExecute(false);
    connect(attackCommand, &Command::executed, this, &Game::attackCommandClicked);
    commandBar.append(attackCommand);

    magicAttackCommand = new Command("qrc:/img/magician.png", tr("Spell"), this);
    magicAttackCommand->setCanExecute(false);
    connect(magicAttackCommand, &Command::executed, this, &Game::magicAttackCommandClicked);
    commandBar.append(magicAttackCommand);

    healCommand = new Command("qrc:/img/heart.png", tr("Heal"), this);
    healCommand->setCanExecute(false);
    connect(healCommand, &Command::executed, this, &Game::healCommandClicked);
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

void Game::initGame(int width, int heigth)
{
    mapHeigth = heigth;
    mapWidth = width;

    map = new Map(mapWidth, mapHeigth, this);

    connect(map, &Map::winner, this, &Game::endGame);

    emit mapHasChanged();
}

void Game::endGame(int winner)
{
    emit gameFinished(winner);

    delete map;
}

int Game::getRoundNum() const
{
    return roundNum;
}

int Game::getRoundPlayer() const
{
    return roundPlayer;
}

Map *Game::getMap() const
{
    return map;
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
    map->resetProperties();

    selectedEntity = nullptr;
    moveCommand->setCanExecute(false);
    attackCommand->setCanExecute(false);
    healCommand->setCanExecute(false);

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

    /* now that I changed the player turn, I increment the star of its castles */
    foreach (Castle *castle, map->getCastles()) {
        if (castle->getPlayerOwner() == roundPlayer) {
            castle->incrementNumStars();
        }
    }


    emit roundPlayerChanged();
}

/*!
 * \brief Move Command Clicked.
 */
void Game::moveCommandClicked()
{
    if (status != Move) map->resetTiles();

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
    if (status != Attack) map->resetTiles();

    if (selectedEntity) {
        status = Attack;

        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        map->availableCharacterToAttack(*character);
    }
}

/*!
 * \brief  Special attack that can only be executed by Magicians.
 * \details All enemies loose 2 lifepoints.
 */
void Game::magicAttackCommandClicked()
{
    map->resetTiles();
    if (selectedEntity) {

        foreach (Character *character, map->getCharacters()) {
            if (character->getPlayerOwner() != selectedEntity->getPlayerOwner()) {
                character->inflictDamage(2);
            }
        }

        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        character->decreaseAttackAvailable();
        character->decreaseMovesAvailable();
    }

    checkPermittedActions();
}

void Game::healCommandClicked() {
    qDebug() << "Heal command clicked!";
    if (selectedEntity) {
        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        character->heal();
    }

    checkPermittedActions();
}

/*!
 * \brief Handling of the click on a castle
 */
void Game::castleClicked(Castle *castle)
{
    if (castle == nullptr) return;

    if (castle->getPlayerOwner() == roundPlayer) {
        selectedEntity = castle;
    }

    status = Idle;
    map->resetTiles();
    checkPermittedActions();
}

/*!
 * \brief Handling of the click on a character.
 * \param x     x of the character clicked
 * \param y     y of the character clicked
 * \details x and y are useful properties to get a reference to the
 * character clicked.
 */
void Game::characterClicked(Character *character)
{
    switch (status) {
    case Idle:
        onIdleState(character);
        break;
    case Move:
        onMoveState(character);
        break;
    case Attack:
        onAttackState(character);
        break;
    default:
        break;
    }

    checkPermittedActions();
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
        onAttackState(tile);
        break;
    default:
        break;
    }

    checkPermittedActions();
}

void Game::onIdleState(Character *character)
{
    if (character == nullptr) {
        selectedEntity = nullptr;
        map->resetTiles();
        return;
    }

    if (character->getPlayerOwner() != roundPlayer) {
        qDebug() << "Entity owner:" << character->getPlayerOwner()
                 << " Round Player:" << roundPlayer;
        return;
    }

    selectedEntity = character;
}

/*!
 * \brief Handling of idle state clicks on the map.
 */
void Game::onIdleState(Tile *tile)
{  
    Q_UNUSED(tile)
    selectedEntity = nullptr;
    map->resetTiles();
}

void Game::onMoveState(Character *character)
{
    Q_UNUSED(character)
    map->resetTiles();
    status = Idle;
}

/*!
 * \brief Handling of Move state clicks on the map.
 */
void Game::onMoveState(Tile *tile)
{
    if (tile->isFree()) {
        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        map->moveCharacterToTile(tile, character);
    }

    map->resetTiles();
    status = Idle;
}

void Game::onAttackState(Character *character)
{
    int x = character->getX();
    int y = character->getY();

    if (map->isTileUnderAttack(x, y)) {
        Character *attacker = dynamic_cast<Character*>(selectedEntity.data());
        attacker->attack(character);
    }

    map->resetTiles();
    status = Idle;
}


/*!
 * \brief Handling od Attack state clicks on the map.
 */
void Game::onAttackState(Tile *tile)
{    
    Q_UNUSED(tile)
    map->resetTiles();
    status = Idle;
}

/*!
 * \brief Game::checkPermittedActions
 */
void Game::checkPermittedActions()
{
    if (!selectedEntity) {
        moveCommand->setCanExecute(false);
        attackCommand->setCanExecute(false);
        healCommand->setCanExecute(false);
        magicAttackCommand->setCanExecute(false);
        return;
    }

    if (dynamic_cast<Character*>(selectedEntity.data())) {
        Character *character = dynamic_cast<Character*>(selectedEntity.data());

        attackCommand->setCanExecute(false);
        if (character->canAttack()) {
            if (map->canAttackSomebody(*character)) {
                attackCommand->setCanExecute(true);
            } else
                attackCommand->setCanExecute(false);
        } else
            attackCommand->setCanExecute(false);

        if (character->canMove()) {
            moveCommand->setCanExecute(true);
        } else
            moveCommand->setCanExecute(false);


        if (character->canHeal()) {
            healCommand->setCanExecute(true);
        } else
            healCommand->setCanExecute(false);

        magicAttackCommand->setCanExecute(false);
        /* check if the selected character is a magician */
        if (dynamic_cast<Magician*>(selectedEntity.data())) {
            Magician *magician = dynamic_cast<Magician*>(selectedEntity.data());

            if (magician->canAttack()) {
                if (map->canAttackSomebody(*character)) {
                    magicAttackCommand->setCanExecute(true);
                } else
                    magicAttackCommand->setCanExecute(false);
            } else
                magicAttackCommand->setCanExecute(false);
        }
    } else if (dynamic_cast<Castle*>(selectedEntity.data())) {
        qDebug() << "It's a castle!";
    }
}
