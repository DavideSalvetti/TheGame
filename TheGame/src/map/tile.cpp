#include "tile.h"
#include <QDebug>

Tile::Tile(int x, int y, QObject *parent)
    : QObject{parent},
      x(x),
      y(y)
{

}

Tile::~Tile()
{
    //    qDebug() << "Deleting tile object.";
}

int Tile::getX()
{
    return x;
}

int Tile::getY()
{
    return y;
}

bool Tile::canMoveOnTile()
{
    return !solid && !character;
}

bool Tile::isFree()
{
    return free;
}

void Tile::setSolid(bool solid)
{
    this->solid = solid;
}

void Tile::setFree(bool free)
{
    this->free = free;
    emit freeChanged();
}

void Tile::addCharacter(Character *character)
{
    if (character != nullptr) {
        this->character = character;
        this->character->move(x, y);
    }

    emit characterChanged();
}

void Tile::removeCharacter() {
    character = nullptr;

    emit characterChanged();
}

Character *Tile::getCharacter()
{
    if (character) {
        //qDebug() << character.data()->getImageSrc();
        return character;
    }

    return nullptr;
}
