#include "staticentity.h"
#include <QDebug>

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
