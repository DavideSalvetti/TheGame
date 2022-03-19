#include "magician.h"

Magician::Magician(QObject *parent)
    : Character{parent}
{
    lifePoints = 6;
    attackPoints = 5;
    defPoints = 2;
}
