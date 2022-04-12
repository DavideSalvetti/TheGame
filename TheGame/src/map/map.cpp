#include "map.h"

#include <QDebug>
#include "../entity/characterfactory.h"

Map::Map(int width, int height, QObject *parent)
    : QObject{parent},
      width(width),
      height(height)
{
    for (int i = 0; i < this->width; i++) {
        QVector<Tile*> tempVector;
        for (int j = 0; j < this->height; j++) {
            Tile *tile = new Tile(i, j, this);
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
}

QQmlListProperty<Tile> Map::getTiles()
{
    return QQmlListProperty<Tile>(this, &tilesList);
}

void Map::populateMap()
{
    Character *swordsman = CharacterFactory::getInstance().createSwordsman();
    swordsman->setParent(this);
    swordsman->setPlayerOwner(PLAYER_1);
    charactersPlayer1.append(swordsman);
    tilesMatrix[0][0]->addCharacter(swordsman);

    swordsman = CharacterFactory::getInstance().createSwordsman();
    swordsman->setParent(this);
    swordsman->setPlayerOwner(PLAYER_2);
    charactersPlayer2.append(swordsman);
    tilesMatrix[height - 1][width - 1]->addCharacter(swordsman);
}

/*!
 * \brief A character has been destroyed. Need to remove the pointer from the array.
 */
void Map::characterDestroyed()
{
    Character *character = dynamic_cast<Character*>(sender());

    // Remove Character from Tile
    int oldX = character->getX();
    int oldY = character->getY();

    tilesMatrix[oldX][oldY]->removeCharacter();


    // Remove Character from vector
    if (character->getPlayerOwner() == PLAYER_1) {
        for (int i = 0; i < charactersPlayer1.size(); i++) {
            if (charactersPlayer1.at(i) == character) {
                charactersPlayer1.remove(i);
                break;
            }
        }
    } else {
        for (int i = 0; i < charactersPlayer2.size(); i++) {
            if (charactersPlayer2.at(i) == character) {
                charactersPlayer2.remove(i);
                break;
            }
        }
    }

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
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {

            if (i == x && j == y)
                tilesMatrix[i][j]->setFree(false);

            if (!tilesMatrix[i][j]->canMoveOnTile())
                tilesMatrix[i][j]->setFree(false);
            else if (abs(x - i) <= maxRange && abs(y - j) <= maxRange) {
                tilesMatrix[i][j]->setFree(true);
                qDebug() << "Tile" << i << j << " is free.";
            } else
                tilesMatrix[i][j]->setFree(false);
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

    // verificare le celle nel range di attacco se contengono un nemico
    int maxRange = character.getAttackRange();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {

            // I cannot attack myself... or at least I think
            if (i == x && j == y)
                tilesMatrix[i][j]->setUnderAttack(false);

            // need to check if there is an enemy on the tile
            Character *enemy = tilesMatrix[i][j]->getCharacter();

            if (enemy == nullptr) {
                tilesMatrix[i][j]->setUnderAttack(false);
                continue;
            }

            // I found an enemy
            if (enemy->getPlayerOwner() != character.getPlayerOwner()) {

                // Let's see if it is in range
                if (abs(x - i) <= maxRange && abs(y - j) <= maxRange
                        && !tilesMatrix[i][j]->isUnderAttack()) {
                    tilesMatrix[i][j]->setUnderAttack(true);
                    continue;
                }
            }

            tilesMatrix[i][j]->setUnderAttack(false);
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
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {

            Character *enemy = tilesMatrix[i][j]->getCharacter();

            if (enemy == nullptr) {
                qDebug() << "Tile " << i << j << " - No Character";
                continue;
            }

            if (enemy->getPlayerOwner() != character.getPlayerOwner()) {
                qDebug() << "Tile " << i << j << " - Enemy";
                if (abs(x - i) <= maxRange && abs(y - j) <= maxRange) {
                    canAttack = true;
                    qDebug() << "Tile " << i << j << " - Enemy in range!";
                    break;
                }
            }
        }
    }

    return canAttack;
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
 * \brief Map::resetCharactersProperties
 */
void Map::resetCharactersProperties()
{
    for (int i = 0; i < charactersPlayer1.size(); i++ ) {
        charactersPlayer1.at(i)->resetProperties();
    }

    for (int i = 0; i < charactersPlayer2.size(); i++ ) {
        charactersPlayer2.at(i)->resetProperties();
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

    tilesMatrix[oldX][oldY]->removeCharacter();
    tile->addCharacter(character);

    character->decreaseMovesAvailable();
}


