#include "map.h"

#include <QDebug>
#include "../entity/characterfactory.h"

Map::Map(int width, int height, QObject *parent)
    : QObject{parent},
      width(width),
      height(height)
{
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

    for (int i = 0; i < this->width; i++) {
        QVector<Tile*> tempVector;
        for (int j = 0; j < this->height; j++) {
            Tile *tile = new Tile(j, i, this);
            tempVector.append(tile);
            tilesList.append(tile);
        }
        tilesMatrix.append(tempVector);
    }

    // set the solid tiles
    tilesMatrix[3][0]->setSolid(true);
    tilesMatrix[3][1]->setSolid(true);
    tilesMatrix[3][2]->setSolid(true);
    tilesMatrix[4][5]->setSolid(true);
    tilesMatrix[4][6]->setSolid(true);
    tilesMatrix[4][7]->setSolid(true);

    populateMap();
}

Map::~Map()
{
    qDebug() << "Deleting map object.";

    qDeleteAll(characters.begin(), characters.end());
}

void Map::populateMap()
{
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
}

QQmlListProperty<Tile> Map::getTiles()
{
    return QQmlListProperty<Tile>(this, &tilesList);
}

QQmlListProperty<Character> Map::getCharactersList()
{
    return QQmlListProperty<Character>(this, &characters);
}

/*!
 * \brief Set the color of the available tiles the character can move on to blue.
 */
void Map::availableTileToMoveOn(Character *character)
{
    if (!character)
        return;

    int x = character->getX();
    int y = character->getY();

    int maxRange = character->getMoveRange();
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
 * \brief Search for enemy that the passed character can attack and set
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
 * \brief Map::canAttackSomebody
 * \param character
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

bool Map::isTileUnderAttack(int x, int y) const
{
    return tilesMatrix[y][x]->isUnderAttack();
}

/*!
 * \brief Reset the tile color to green.
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

    character->setX(tile->getX());
    character->setY(tile->getY());
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



