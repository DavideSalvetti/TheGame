#include "ninja.h"
#define MAX_NINJA_LIFEPOINTS 12

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

int Ninja::getMaxLifePoints() const
{
    return MAX_NINJA_LIFEPOINTS;
}

void Ninja::resetProperties()
{
    Knight::resetProperties();
}
