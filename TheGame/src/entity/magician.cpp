#include "magician.h"

Magician::Magician(QObject *parent)
    : Character{parent}
{
    lifePoints = 6;
    attackPoints = 5;
    defPoints = 2;
    magicPoints = 7;
    moveRange = 2;
    attackRange = 3;
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
    imageSrc = ":/img/wizard.png";
}

bool Magician::magicAttack(Character *enemy)
{
    if (this == enemy)
        return false;


    return true;
}
