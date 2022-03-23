#include "swordsman.h"

Swordsman::Swordsman(QObject *parent)
    : Character{parent}
{
    lifePoints = 10;
    attackPoints = 4;
    defPoints = 2;
    moveRange = 2;
    attackRange = 1;
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
    imageSrc = "qrc:/img/swordsman.png";
}
