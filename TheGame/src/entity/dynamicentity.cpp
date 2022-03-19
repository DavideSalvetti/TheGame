#include "dynamicentity.h"

DynamicEntity::DynamicEntity(QObject *parent)
    : Entity{parent}
{

}

void DynamicEntity::move(int x, int y)
{
    this->x = x;
    this->y = y;
}
