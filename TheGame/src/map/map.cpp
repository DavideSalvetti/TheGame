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
