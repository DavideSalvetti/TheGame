#include "tile.h"
#include <QDebug>


namespace game {
namespace map {

Tile::Tile(int x, int y, QObject *parent)
    : QObject{parent},
      x(x),
      y(y)
{

}

Tile::~Tile()
{
    qDebug() << "Deleting tile object." << x << y;
}

int Tile::getX() const
{
    return x;
}

int Tile::getY() const
{
    return y;
}

/*!
 * \brief A character can move on Tile only if the tile is not solid
 * and there are no other entities on it.
 */
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

void Tile::setSolid(const bool solid)
{
    this->solid = solid;
}

void Tile::setFree(const bool free)
{
    this->free = free;
    emit freeChanged();
}

/*!
 * \brief Set if the current tile can be attacked, so we can assign
 * a red color.
 */
void Tile::setUnderAttack(const bool underAttack)
{
    if (this->underAttack == underAttack)
        return;

    this->underAttack = underAttack;
    emit underAttackChanged();
}

/*!
 * \brief Set that an entity is present on the current Tile.
 */
void Tile::setEntityPresent(const bool entityPresent)
{
    if (this->entityPresent == entityPresent)
        return;

    this->entityPresent = entityPresent;
}

}
}
