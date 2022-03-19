#include "map.h"

#include <QDebug>

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
        }
        tilesMatrix.append(tempVector);
    }
}

Map::~Map()
{
    qDebug() << "Deleting map object.";
}
