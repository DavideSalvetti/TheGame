#include "swordsman.h"

Swordsman::Swordsman(QObject *parent)
    : Character{parent}
{
    lifePoints = 10;
    attackPoints = 4;
    defPoints = 2;
    imageSrc = "qrc:/img/swordsman.png";
}
