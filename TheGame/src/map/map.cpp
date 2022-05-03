#include "map.h"

#include <QDebug>
#include <QRandomGenerator>
#include "../entity/characterfactory.h"
#include <random>

namespace game {
namespace map {

using namespace entity;

Map::Map(int width, int height, QObject *parent)
    : QObject{parent},
      width(width),
      height(height)
{
    // base on the width and height, choose the size of the tiles
    if (width == 8) {
        tileWidth = 64;
        tileHeight = 64;
    } else if (width == 12) {
        tileWidth = 56;
        tileHeight = 56;
    } else if (width == 16) {
        tileWidth = 48;
        tileHeight = 48;
    }

    // create the tile objects
    for (int i = 0; i < this->width; i++) {
        QVector<Tile*> tempVector;
        for (int j = 0; j < this->height; j++) {
            Tile *tile = new Tile(j, i, this);
            tempVector.append(tile);
            tilesList.append(tile);
        }
        tilesMatrix.append(tempVector);
    }

    populateMap();
}

Map::~Map()
{
    qDebug() << "Deleting map object.";

    /* delete all the characters inside the list using iterators and Qt library functions */
    qDeleteAll(characters.begin(), characters.end());
}
/*!
 * \brief Add characters to the map, castles, and define solid tiles.
 */
void Map::populateMap()
{
    /* add characters to the map */
    Character *swordsman = CharacterFactory::getInstance().createSwordsman();
    swordsman->setParent(this);
    swordsman->setPlayerOwner(PLAYER_1);
    swordsman->move(0, 0);
    characters.append(swordsman);
    tilesMatrix[0][0]->setEntityPresent(true);
    connect(swordsman, &Character::characterDestroyed, this,
            &Map::removeCharacter);

    Character *archer = CharacterFactory::getInstance().createArcher();
    archer->setParent(this);
    archer->setPlayerOwner(PLAYER_1);
    archer->move(1, 0);
    characters.append(archer);
    tilesMatrix[0][1]->setEntityPresent(true);
    connect(archer, &Character::characterDestroyed, this,
            &Map::removeCharacter);

    Character *magician = CharacterFactory::getInstance().createMagician();
    magician->setParent(this);
    magician->setPlayerOwner(PLAYER_1);
    magician->move(2, 0);
    characters.append(magician);
    tilesMatrix[0][2]->setEntityPresent(true);
    connect(magician, &Character::characterDestroyed, this,
            &Map::removeCharacter);

    swordsman = CharacterFactory::getInstance().createSwordsman();
    swordsman->setParent(this);
    swordsman->setPlayerOwner(PLAYER_2);
    swordsman->move(width - 1, height - 1);
    characters.append(swordsman);
    tilesMatrix[width - 1][height - 1]->setEntityPresent(true);
    connect(swordsman, &Character::characterDestroyed, this,
            &Map::removeCharacter);

    archer = CharacterFactory::getInstance().createArcher();
    archer->setParent(this);
    archer->setPlayerOwner(PLAYER_2);
    archer->move(width - 2, height - 1);
    characters.append(archer);
    tilesMatrix[width - 1][height - 2]->setEntityPresent(true);
    connect(archer, &Character::characterDestroyed, this,
            &Map::removeCharacter);

    magician = CharacterFactory::getInstance().createMagician();
    magician->setParent(this);
    magician->setPlayerOwner(PLAYER_2);
    magician->move(width - 3, height - 1);
    characters.append(magician);
    tilesMatrix[width - 1][height - 3]->setEntityPresent(true);
    connect(magician, &Character::characterDestroyed, this,
            &Map::removeCharacter);

    /* add castles to the map */
    Castle *castle_player1 = new Castle(getMapWidth() - 1, 0, this);
    castle_player1->setPlayerOwner(PLAYER_1);
    castle_player1->incrementNumStars(); // increment the stars because its teh first turn
    castles.append(castle_player1);

    Castle *castle_player2 = new Castle(0, getMapWidth() - 1, this);
    castle_player2->setPlayerOwner(PLAYER_2);
    castles.append(castle_player2);

    /* Select some solid tiles to display based on the size of the map */
    int numSolidTiles = 0;
    if (getMapWidth() <= 8) numSolidTiles = 8;
    else if (getMapWidth() <= 12) numSolidTiles = 16;
    else numSolidTiles = 22;

    std::uniform_int_distribution<int> yDist(2, getMapWidth() - 1 - 2);
    std::uniform_int_distribution<int> xDist(0, getMapWidth() - 1);
    for (int i = 0; i < numSolidTiles; i++) {
        bool alreadySolid = false;
        do {
            alreadySolid = false;
            int x = xDist(*QRandomGenerator::global());
            int y = yDist(*QRandomGenerator::global());

            if (tilesMatrix[y][x]->isSolid()) {
                alreadySolid = true;
            } else {
                tilesMatrix[y][x]->setSolid(true);
            }
        } while (alreadySolid);
    }

}

QQmlListProperty<Tile> Map::getTiles()
{
    return QQmlListProperty<Tile>(this, &tilesList);
}

QQmlListProperty<Character> Map::getCharactersList()
{
    return QQmlListProperty<Character>(this, &characters);
}

QQmlListProperty<Castle> Map::getCastlesList()
{
    return QQmlListProperty<Castle>(this, &castles);
}

QList<Character*> Map::getCharacters()
{
    return characters;
}

QList<Castle *> Map::getCastles()
{
    return castles;
}

/*!
 * \brief Set the color of the available tiles the character can move on to blue.
 */
void Map::availableTileToMoveOn(const Character &character)
{
    int x = character.getX();
    int y = character.getY();

    int maxRange = character.getMoveRange();
    for (int i = x - maxRange; i <= x + maxRange; i++) {
        for (int j = y - maxRange; j <= y + maxRange; j++) {

            if (i < 0 || i >= width || j < 0 || j >= height)
                continue;

            if (i == x && j == y)
                tilesMatrix[j][i]->setFree(false);

            if (!tilesMatrix[j][i]->canMoveOnTile())
                tilesMatrix[j][i]->setFree(false);
            else if (abs(x - i) <= maxRange && abs(y - j) <= maxRange) {
                tilesMatrix[j][i]->setFree(true);
            } else
                tilesMatrix[j][i]->setFree(false);
        }
    }
}

/*!
 * \brief Search for enemy that the \p character can attack and set
 *  the tile to underAttack.
 */
void Map::availableCharacterToAttack(const Character &character)
{
    int x = character.getX();
    int y = character.getY();

    int maxRange = character.getAttackRange();
    for (int i = x - maxRange; i <= x + maxRange; i++) {
        for (int j = y - maxRange; j <= y + maxRange; j++) {

            if (i < 0 || i >= width || j < 0 || j >= height)
                continue;

            // I cannot attack myself... or maybe this can be a new feature?
            if (i == x && j == y)
                tilesMatrix[j][i]->setUnderAttack(false);

            // need to check if there is an enemy on the tile
            Character *enemy = nullptr;
            foreach (Character *item, characters) {
                if (item->getX() == i && item->getY() == j) {
                    enemy = item;
                    break;
                }
            }

            if (enemy == nullptr) {
                tilesMatrix[j][i]->setUnderAttack(false);
                continue;
            }

            // I found an enemy
            if (enemy->getPlayerOwner() != character.getPlayerOwner()) {

                // Let's see if it is in range
                if (abs(x - i) <= maxRange && abs(y - j) <= maxRange
                        && !tilesMatrix[j][i]->isUnderAttack()) {
                    tilesMatrix[j][i]->setUnderAttack(true);
                    continue;
                }
            }

            tilesMatrix[j][i]->setUnderAttack(false);
        }
    }
}
/*!
 * \brief Search for enemy that \p character can attack on the map.
 * \return True if there is at least one enemy to attack, false otherwise
 */
bool Map::canAttackSomebody(const Character &character)
{
    int x = character.getX();
    int y = character.getY();

    bool canAttack = false;
    int maxRange = character.getAttackRange();
    for (int i = x - maxRange; i <= x + maxRange; i++) {
        for (int j = y - maxRange; j <= y + maxRange; j++) {

            if (i < 0 || i >= width || j < 0 || j >= height)
                continue;

            if (i == x && j == y)
                continue;

            Character *enemy = nullptr;
            foreach (Character *item, characters) {
                if (item->getX() == i && item->getY() == j) {
                    enemy = item;
                    break;
                }
            }

            if (enemy == nullptr) {
                continue;
            }

            if (enemy->getPlayerOwner() != character.getPlayerOwner()) {
                if (abs(x - i) <= maxRange && abs(y - j) <= maxRange) {
                    canAttack = true;
                    break;
                }
            }
        }
    }

    return canAttack;
}

/*!
 * \brief Check is the tile at \p x \p y is under attack or not.
 * \return True if the tile is under attack.
 */
bool Map::isTileUnderAttack(int x, int y) const
{
    return tilesMatrix[y][x]->isUnderAttack();
}

/*!
 * \brief Reset the tile color to normal.
 */
void Map::resetTiles()
{
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            tilesMatrix[i][j]->setFree(false);
            tilesMatrix[i][j]->setUnderAttack(false);
        }
    }
}

/*!
 * \brief Move the character to the given tile.
 * \param tile      - Tile where the character needs to be moved
 * \param character - Character that needs to be moved
 */
void Map::moveCharacterToTile(Tile *tile, Character *character) {

    int oldX = character->getX();
    int oldY = character->getY();

    character->move(tile->getX(), tile->getY());
    tilesMatrix[oldY][oldX]->setEntityPresent(false);
    tile->setEntityPresent(true);

    character->decreaseMovesAvailable();
}

/*!
 * \brief Reset the properties of each character at the end of the turn.
 */
void Map::resetProperties()
{
    foreach (Character *character, characters) {
        character->resetProperties();
    }
}

/*!
 * \brief Create a new character and add it to the list of characters of the
 * current player.
 * \param x
 * \param y
 * \param player
 * \param itemSelected
 */
void Map::addCharacter(int x, int y, Owner player, int itemSelected)
{
    Character *character = nullptr;
    if (itemSelected == 1)
        character = CharacterFactory::getInstance().createSwordsman();
    else if (itemSelected == 2)
        character = CharacterFactory::getInstance().createArcher();
    else if (itemSelected == 3)
        character = CharacterFactory::getInstance().createMagician();
    else if (itemSelected == 4)
        character = CharacterFactory::getInstance().createWarrior();
    else if (itemSelected == 5)
        character = CharacterFactory::getInstance().createNinja();
    else
        qFatal("Must implement new characters.");

    if (character) {
        character->move(x, y);
        character->setPlayerOwner(player);
        character->decreaseMovesAvailable();
        character->decreaseAttackAvailable();
        characters.append(character);

        connect(character, &Character::characterDestroyed, this,
                &Map::removeCharacter);
    }

    emit characterListChanged();

}

int Map::getMapWidth() const
{
    return width;
}

int Map::getMapHeight() const
{
    return height;
}

int Map::getTileWidth() const
{
    return tileWidth;
}

int Map::getTileHeight() const
{
    return tileHeight;
}

/*!
 * \brief A character has been destroyed. Remove it from the List and delete it.
 * \param x - x coordinate where the character to remove is
 * \param y - y coordinate where the character to remove is
 */
void Map::removeCharacter(int x, int y)
{
    for (int i = 0; i < characters.size(); i++) {
        if (characters.at(i)->getX() == x && characters.at(i)->getY() == y) {
            int x = characters.at(i)->getX();
            int y = characters.at(i)->getY();

            tilesMatrix[y][x]->setEntityPresent(false);
            delete characters.takeAt(i);
        }
    }

    emit characterListChanged();

    /* Check if players have other characters, otherwise the game has finished */
    int numCharactersPlayer1 = 0;
    int numCharactersPlayer2 = 0;
    foreach (Character *character, characters) {
        if (character->getPlayerOwner() == PLAYER_1)
            numCharactersPlayer1++;
        if (character->getPlayerOwner() == PLAYER_2)
            numCharactersPlayer2++;
    }

    if (numCharactersPlayer1 == 0) {
        resetTiles();
        emit winner(PLAYER_2);
    }
    if (numCharactersPlayer2 == 0) {
        resetTiles();
        emit winner(PLAYER_1);
    }
}

bool Map::isCharacterOnTile(int x, int y)  const
{
    if (x > getMapWidth() || y > getMapHeight())
        return false;

    return tilesMatrix[y][x]->isEntityPresent();
}

}
}



