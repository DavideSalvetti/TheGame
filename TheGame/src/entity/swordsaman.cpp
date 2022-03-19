#include "swordsaman.h"

Swordsaman::Swordsaman(QObject *parent)
    : Character{parent}
{
    lifePoints = 10;
    attackPoints = 4;
    defPoints = 2;
}
