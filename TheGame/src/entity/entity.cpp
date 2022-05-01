#include "entity.h"
#include <QDebug>

namespace game {
namespace entity {

Entity::Entity(QObject *parent)
    : QObject{parent},
      playerOwner(NONE)
{

}

Entity::~Entity()
{
    qDebug() << "Entity destroyed";
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

}
}
