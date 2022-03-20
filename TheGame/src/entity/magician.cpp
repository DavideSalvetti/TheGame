#include "magician.h"

Magician::Magician(QObject *parent)
    : Character{parent}
{
    lifePoints = 6;
    attackPoints = 5;
    defPoints = 2;
    magicPoints = 7;
}

bool Magician::magicAttack(Character *enemy)
{
    if (this == enemy)
        return false;


    return true;
}
