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
            Tile *tile = new Tile(this);
            tempVector.append(tile);
            tilesList.append(tile);
        }
        tilesMatrix.append(tempVector);
    }

    populateField();
}

Map::~Map()
{
    qDebug() << "Deleting map object.";
}

QQmlListProperty<Tile> Map::getTiles()
{
    return QQmlListProperty<Tile>(this, &tilesList);
}

void Map::populateField()
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
 * \brief Set the color of the available tiles the character can move on to blue.
 */
void Map::availableTileToMoveOn(Character *character)
{
    if (!character)
        return;

    int x = character->getX();
    int y = character->getY();

    int maxRange = 2;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {

            if (i == x && j == y)
                tilesMatrix[i][j]->setFree(false);

            if (!tilesMatrix[i][j]->canMoveOnTile())
                tilesMatrix[i][j]->setFree(false);
            else if (abs(x - i) < maxRange && abs(y - j) < maxRange) {
                tilesMatrix[i][j]->setFree(true);
                qDebug() << "Tile" << i << j << " is free.";
            } else
                tilesMatrix[i][j]->setFree(false);
        }
    }
}


