#include "game.h"
#include <QDebug>

#include "entity/characterfactory.h"

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

    healCommand = new Command("qrc:/img/heart.png", tr("Heal"), this);
    healCommand->setCanExecute(false);
    connect(healCommand, &Command::executed, this, &Game::healCommandClicked);
    commandBar.append(healCommand);

    nextTurnCommand = new Command("qrc:/img/check.png", tr("End Turn"), this);
    nextTurnCommand->setCanExecute(true);
    connect(nextTurnCommand, &Command::executed, this, &Game::endTurn);
    commandBar.append(nextTurnCommand);

    mapHeigth = 8;
    mapWidth = 8;

    charactersModel = new CharactersModel(this);
    initGame();
}

Game & Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::initGame()
{
    map.reset(new Map(mapWidth,mapHeigth));

    Character *swordsman = CharacterFactory::getInstance().createSwordsman();
    swordsman->setParent(this);
    swordsman->setPlayerOwner(PLAYER_1);
    swordsman->move(0, 0);
    characters.append(swordsman);
    //    charactersModel->addCharacter(swordsman);
    connect(swordsman, &Character::characterDestroyed, this,
            &Game::removeCharacter);

    Character *archer = CharacterFactory::getInstance().createArcher();
    archer->setParent(this);
    archer->setPlayerOwner(PLAYER_1);
    archer->move(1, 0);
    characters.append(archer);
    //    charactersModel->addCharacter(archer);
    connect(archer, &Character::characterDestroyed, this,
            &Game::removeCharacter);

    Character *magician = CharacterFactory::getInstance().createMagician();
    magician->setParent(this);
    magician->setPlayerOwner(PLAYER_1);
    magician->move(2, 0);
    characters.append(magician);
    //    charactersModel->addCharacter(magician);
    connect(magician, &Character::characterDestroyed, this,
            &Game::removeCharacter);

    swordsman = CharacterFactory::getInstance().createSwordsman();
    swordsman->setParent(this);
    swordsman->setPlayerOwner(PLAYER_2);
    swordsman->move(mapWidth - 1, mapHeigth - 1);
    characters.append(swordsman);
    //    charactersModel->addCharacter(swordsman);
    connect(swordsman, &Character::characterDestroyed, this,
            &Game::removeCharacter);

    archer = CharacterFactory::getInstance().createArcher();
    archer->setParent(this);
    archer->setPlayerOwner(PLAYER_2);
    archer->move(mapWidth - 2, mapHeigth - 1);
    characters.append(archer);
    //    charactersModel->addCharacter(archer);
    connect(archer, &Character::characterDestroyed, this,
            &Game::removeCharacter);

    magician = CharacterFactory::getInstance().createMagician();
    magician->setParent(this);
    magician->setPlayerOwner(PLAYER_2);
    magician->move(mapWidth - 3, mapHeigth - 1);
    characters.append(magician);
    //    charactersModel->addCharacter(magician);
    connect(magician, &Character::characterDestroyed, this,
            &Game::removeCharacter);
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
    return map.data();
}

CharactersModel *Game::getCharacters() const
{
    return charactersModel;
}

QQmlListProperty<Command> Game::getCommandBar()
{
    return QQmlListProperty<Command>(this, &commandBar);
}

QQmlListProperty<Character> Game::getCharactersList()
{
    return QQmlListProperty<Character>(this, &characters);
}

/*!
 * \brief End turn and initialization of properties for the next one.
 */
void Game::endTurn()
{

    status = Idle;
    map->resetTiles();

    foreach (Character *character, characters) {
        character->resetProperties();
    }

    charactersModel->resetProperties();

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

    emit roundPlayerChanged();
}

/*!
 * \brief Move Command Clicked.
 */
void Game::moveCommandClicked()
{
    qDebug() << "Move command clicked!";

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
    qDebug() << "Attack command clicked!";

    if (status != Attack) map->resetTiles();

    if (selectedEntity) {
        status = Attack;

        Character *character = dynamic_cast<Character*>(selectedEntity.data());
        map->availableCharacterToAttack(*character, characters);
    }
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
 * \brief Handling of the click on a character.
 * \param x     x of the character clicked
 * \param y     y of the character clicked
 * \details x and y are useful properties to get a reference to the
 * character clicked.
 */
void Game::characterClicked(Character *character)
{
    qDebug() << "Character Clicked!";
    //    Character *character = charactersModel->getCharacter(x, y);

    switch (status) {
    case Idle:
        onIdleState(character);
        break;
        //    case Move:
        //        onMoveState(tile);
        //        break;
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
    qDebug() << "Tile Clicked!";

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
        return;
    }

    if (dynamic_cast<Character*>(selectedEntity.data())) {
        Character *character = dynamic_cast<Character*>(selectedEntity.data());

        attackCommand->setCanExecute(false);
        if (character->canAttack()) {
            if (map->canAttackSomebody(*character, characters)) {
                qDebug() << "Can Attack";
                attackCommand->setCanExecute(true);
            } else
                attackCommand->setCanExecute(false);
        } else
            attackCommand->setCanExecute(false);

        if (character->canMove()) {
            moveCommand->setCanExecute(true);
            qDebug() << "Can Move";
        } else
            moveCommand->setCanExecute(false);


        if (character->canHeal()) {
            healCommand->setCanExecute(true);
            qDebug() << "Can Heal";
        } else
            healCommand->setCanExecute(false);
    }
}

void Game::removeCharacter(int x, int y)
{
    for (int i = 0; i < characters.size(); i++) {
        if (characters.at(i)->getX() == x && characters.at(i)->getY() == y) {
            // qui bisogna togliere EntityPresent al tile a cui appartiene
            // il character da eliminare
            delete characters.takeAt(i);
        }
    }

    emit characterListChanged();
}
