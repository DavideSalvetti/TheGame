#include "game.h"
#include <QDebug>


/*!
 * \class Game
 * \details Singleton for the management of the game.
 */

Game::Game(QObject *parent)
    : QObject{parent},
      roundNum(1),
      roundPlayer(1)
{

    qDebug() << "Game Singleton Created!";

    nextTurnCommand = new Command("qrc:/img/check.png", tr("End Turn"), this);
    nextTurnCommand->setCanExecute(true);
    connect(nextTurnCommand, &Command::executed, this, &Game::endTurn);
    commandBar.append(nextTurnCommand);

    createCommand = new Command("qrc:/img/swords.png", tr("Add Unit"), this);
    createCommand->setCanExecute(false);
    connect(createCommand, &Command::executed, this, &Game::createCommandClicked);
    commandBar.append(createCommand);

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

    incrementAttackCommand = new Command("qrc:/img/level-up.png", tr("Power up"), this);
    incrementAttackCommand->setCanExecute(false);
    connect(incrementAttackCommand, &Command::executed, this, &Game::incrementAttackCommandClicked);
    commandBar.append(incrementAttackCommand);

    healCommand = new Command("qrc:/img/heart.png", tr("Heal"), this);
    healCommand->setCanExecute(false);
    connect(healCommand, &Command::executed, this, &Game::healCommandClicked);
    commandBar.append(healCommand);
}

Game & Game::getInstance()
{
    static Game instance;
    return instance;
}

Game::~Game()
{
    qDebug() << "Deleting Singleton Game!";
}

/*!
 * \brief Initialize the game creating the map with the given \p width and \p height,
 */
void Game::initGame(int width, int heigth)
{
    mapHeigth = heigth;
    mapWidth = width;

    map = new Map(mapWidth, mapHeigth, this);
    connect(map, &Map::winner, this, &Game::endGame);

    emit mapHasChanged();
}

/*!
 * \brief Send the signal that there is a winner and deletes the map.
 * \details There is no need to check if the map has already been deeleted,
 * because the signal to this slot is sent from the map object, so it must
 * be available.
 */
void Game::endGame(int winner)
{
    emit gameFinished(winner);

    /* delete the map and all its childs */
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
 * \brief Set the selected character to the QmlEngine.
 * \details Dynamic Cast is used at runtime to check if the type can be converted to a
 * specific type. In this case, it's easier than typeId, because I don't want to know
 * the current type (Swordsman, Archer, ...) but I want to know if it can be converted to
 * Character (that is an abstract class).
 */
Character *Game::getSelectedCharacter() const
{
    Character *character = dynamic_cast<Character*>(selectedEntity.data());
    if (character)
        return character;

    return nullptr;
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
    createCommand->setCanExecute(false);
    magicAttackCommand->setCanExecute(false);
    incrementAttackCommand->setCanExecute(false);

    nextPlayer();

    emit selectedCharacterChanged();
}

/*!
 * \brief Add a new unit to the game.
 */
void Game::addUnit(int itemSelected)
{
    if (selectedEntity) {
        Castle *castle = dynamic_cast<Castle*>(selectedEntity.data());
        map->addCharacter(castle->getX(), castle->getY(),
                          static_cast<Owner>(roundPlayer), itemSelected);
        castle->reduceNumStars(itemSelected);
    }

    checkPermittedActions();
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
 * \brief Create command clicked.
 */
void Game::createCommandClicked()
{
    if (selectedEntity) {
        Castle *castle = dynamic_cast<Castle*>(selectedEntity.data());

        if (castle)
            emit createUnitClicked(castle->getNumStars());
    }
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
        if (character)
            map->availableTileToMoveOn(*character);
    }
}

/*!
 * \brief Attack Command Clicked.
 */
void Game::attackCommandClicked() {
    if (status != Attack) map->resetTiles();

    if (selectedEntity) {
        status = Attack;

        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        if (character)
            map->availableCharacterToAttack(*character);
    }
}

/*!
 * \brief  Special attack that can only be executed by Magicians.
 * \details All enemies loose 2 lifepoints, but not Magician (and derived classes).
 */
void Game::magicAttackCommandClicked()
{
    map->resetTiles();
    if (selectedEntity) {
        foreach (Character *character, map->getCharacters()) {
            if (character->getPlayerOwner() != selectedEntity->getPlayerOwner()) {
                if (!dynamic_cast<Magician*>(character))
                    character->inflictDamage(2);
            }
        }

        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        character->decreaseAttackAvailable();
        character->decreaseMovesAvailable();
    }

    checkPermittedActions();
}

/*!
 * \brief The selectedEntity increase its attack points.
 * \details Can be done only with Knight (and derived classes).
 */
void Game::incrementAttackCommandClicked()
{
    map->resetTiles();
    if (selectedEntity) {
        Knight *knight = dynamic_cast<Knight*>(selectedEntity.data());
        if (knight)
            knight->incrementAttackPoints();
    }

    checkPermittedActions();
}

void Game::healCommandClicked()
{
    if (selectedEntity) {
        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        if (character)
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
        emit selectedCharacterChanged();
    }

    status = Idle;
    map->resetTiles();
    checkPermittedActions();
}

/*!
 * \brief Handling of the click on a character.
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
        emit selectedCharacterChanged();
        return;
    }

    if (character->getPlayerOwner() != roundPlayer) {
        return;
    }

    selectedEntity = character;
    emit selectedCharacterChanged();
}

/*!
 * \brief Handling of idle state clicks on the map.
 */
void Game::onIdleState(Tile *tile)
{  
    Q_UNUSED(tile)
    selectedEntity = nullptr;
    map->resetTiles();

    emit selectedCharacterChanged();
}

void Game::onMoveState(Character *character)
{
    Q_UNUSED(character)
    map->resetTiles();
    status = Idle;

    onIdleState(character);
}

/*!
 * \brief Handling of Move state clicks on the map.
 */
void Game::onMoveState(Tile *tile)
{
    if (tile->isFree()) {
        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        if (character)
            map->moveCharacterToTile(tile, character);
    }

    map->resetTiles();
    status = Idle;
}

/*!
 * \brief Handling of the Attack command.
 */
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
 * \brief Check which actions the selectedEntity can perform.
 * \details For the same reasons of \p getSelectedCharacter() I used
 * dynamic casts.
 */
void Game::checkPermittedActions()
{
    moveCommand->setCanExecute(false);
    attackCommand->setCanExecute(false);
    healCommand->setCanExecute(false);
    magicAttackCommand->setCanExecute(false);
    createCommand->setCanExecute(false);
    incrementAttackCommand->setCanExecute(false);

    if (!selectedEntity)
        return;

    Character * character = dynamic_cast<Character*>(selectedEntity.data());
    if (character) {
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
        Magician *magician = dynamic_cast<Magician*>(selectedEntity.data());
        if (magician) {

            if (magician->canMagicAttack()) {
                magicAttackCommand->setCanExecute(true);
            } else
                magicAttackCommand->setCanExecute(false);
        }

        /* check if the selected character is a knight */
        Knight *knight = dynamic_cast<Knight*>(selectedEntity.data());
        if (knight) {

            if (knight->canIncrementAttackPoints()) {
                incrementAttackCommand->setCanExecute(true);
            } else {
                incrementAttackCommand->setCanExecute(false);
            }
        }

    } else if (dynamic_cast<Castle*>(selectedEntity.data())) {
        Castle *castle = dynamic_cast<Castle*>(selectedEntity.data());
        if (castle->getNumStars() > 0) {
            if (!map->isCharacterOnTile(castle->getX(), castle->getY())) {
                createCommand->setCanExecute(true);
            }
        }
    }
}
