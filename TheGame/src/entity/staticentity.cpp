#include "staticentity.h"
#include <QDebug>

namespace game {
namespace entity {

StaticEntity::StaticEntity(int xPos, int yPos, QObject *parent)
    : Entity{parent}
{
    x = xPos;
    y = yPos;
}

StaticEntity::~StaticEntity()
{
    qDebug() << "Deleting StaticEntity";
}

}
}
