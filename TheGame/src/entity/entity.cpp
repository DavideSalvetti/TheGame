#include "entity.h"

Entity::Entity(QObject *parent)
    : QObject{parent},
      playerOwner(NONE)
{

}

void Entity::setPlayerOwner(Owner owner)
{
    this->playerOwner = owner;
}

Owner Entity::getPlayerOwner() const
{
    return playerOwner;
}

int Entity::getX() const
{
    return x;
}

int Entity::getY() const
{
    return y;
}
