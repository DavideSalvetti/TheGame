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

}

Map::~Map()
{
    qDebug() << "Deleting map object.";
}

QQmlListProperty<Tile> Map::getTiles()
{
    return QQmlListProperty<Tile>(this, &tilesList);
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
                qDebug() << "Tile" << i << j << " is free.";
            } else
                tilesMatrix[j][i]->setFree(false);
        }
    }
}

/*!
 * \brief Search for enemy that the passed character can attack and set
 *  the tile to underAttack.
 */
void Map::availableCharacterToAttack(const Character &character, const QList<Character*> &characters)
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
bool Map::canAttackSomebody(const Character &character, const QList<Character*> &characters)
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
    tilesMatrix[oldX][oldY]->setEntityPresent(false);
    tile->setEntityPresent(true);

    character->decreaseMovesAvailable();
}



