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

int Tile::getX() const
{
    return x;
}

int Tile::getY() const
{
    return y;
}

bool Tile::canMoveOnTile()
{
    return !solid && !character;
}

bool Tile::isFree() const
{
    return free;
}

bool Tile::isUnderAttack() const
{
    return underAttack;
}

bool Tile::isSolid() const
{
    return solid;
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

void Tile::setUnderAttack(bool underAttack)
{
    if (this->underAttack == underAttack)
        return;

    this->underAttack = underAttack;
    emit underAttackChanged();
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
        return character;
    }

    return nullptr;
}
