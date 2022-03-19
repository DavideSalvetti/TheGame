#include "archer.h"

Archer::Archer(QObject *parent)
    : Character{parent}
{
    lifePoints = 10;
    attackPoints = 3;
    defPoints = 1;
}
