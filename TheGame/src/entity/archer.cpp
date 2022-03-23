#include "archer.h"

Archer::Archer(QObject *parent)
    : Character{parent}
{
    lifePoints = 10;
    attackPoints = 3;
    defPoints = 1;
    moveRange = 2;
    attackRange = 3;
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
    imageSrc = ":/img/bow.png";
}
