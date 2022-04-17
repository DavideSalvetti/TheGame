#include "dynamicentity.h"
#include <QDebug>

DynamicEntity::DynamicEntity(QObject *parent)
    : Entity{parent}
{

}

DynamicEntity::~DynamicEntity()
{
    qDebug() << "DynamicEntity Destroyed";
}
