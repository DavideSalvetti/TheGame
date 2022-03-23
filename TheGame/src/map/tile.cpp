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
    if (character != nullptr)
        this->character = character;

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
