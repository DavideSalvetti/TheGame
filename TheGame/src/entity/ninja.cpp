#include "ninja.h"
#include <QDebug>

#define MAX_NINJA_LIFEPOINTS 12

namespace game {
namespace entity {

Ninja::Ninja(QObject *parent)
    : Magician{parent},
      Knight{parent}
{
    lifePoints = MAX_NINJA_LIFEPOINTS;
    attackPoints = 4;
    defPoints = 3;
    moveRange = 3;
    attackRange = 1;
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
    imageSrc = "qrc:/img/ninja.png";
}

Ninja::~Ninja()
{
    qDebug() << "Ninja Destroyed";
}

int Ninja::getMaxLifePoints() const
{
    return MAX_NINJA_LIFEPOINTS;
}

void Ninja::resetProperties()
{
    Knight::resetProperties();
}

}
}
