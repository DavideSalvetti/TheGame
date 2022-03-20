#include "tile.h"
#include <QDebug>

Tile::Tile(QObject *parent)
    : QObject{parent}
{

}

Tile::~Tile()
{
    //    qDebug() << "Deleting tile object.";
}

bool Tile::canMoveOnTile()
{
    return free && !solid;
}

void Tile::setSolid(bool solid)
{
    this->solid = solid;
}

void Tile::setFree(bool free)
{
    this->free = free;
}

void Tile::addCharacter(Character *character)
{
    if (this->character)
        this->character = character;
}
