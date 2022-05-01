#include "dynamicentity.h"
#include <QDebug>

namespace game {
namespace entity {

DynamicEntity::DynamicEntity(QObject *parent)
    : Entity{parent}
{

}

DynamicEntity::~DynamicEntity()
{
    qDebug() << "DynamicEntity Destroyed";
}

}
}
