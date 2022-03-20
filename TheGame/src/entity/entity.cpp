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

Owner Entity::getPlayerOwner()
{
    return playerOwner;
}
