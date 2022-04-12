#include "magician.h"

#define MAX_MAGICIAN_LIFEPOINTS 6

Magician::Magician(QObject *parent)
    : Character{parent}
{
    lifePoints = MAX_MAGICIAN_LIFEPOINTS;
    attackPoints = 5;
    defPoints = 2;
    magicPoints = 7;
    moveRange = 2;
    attackRange = 3;
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
    imageSrc = "qrc:/img/wizard.png";
}

bool Magician::magicAttack(Character *enemy)
{
    if (this == enemy)
        return false;


    return true;
}

int Magician::getMaxLifePoints() const
{
    return MAX_MAGICIAN_LIFEPOINTS;
}

void Magician::resetProperties()
{
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
}
