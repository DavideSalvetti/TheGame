#include "entity.h"
#include <QDebug>

Entity::Entity(QObject *parent)
    : QObject{parent},
      playerOwner(NONE)
{

}

Entity::~Entity()
{
    qDebug() << "Entity destroyed";
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
