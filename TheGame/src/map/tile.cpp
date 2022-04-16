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
    qDebug() << "Deleting tile object.";
}

int Tile::getX() const
{
    return x;
}

int Tile::getY() const
{
    return y;
}

bool Tile::canMoveOnTile() const
{
    return !solid && !entityPresent;
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

bool Tile::isEntityPresent() const
{
    return entityPresent;
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

void Tile::setEntityPresent(bool entityPresent)
{
    if (this->entityPresent == entityPresent)
        return;

    this->entityPresent = entityPresent;
}
