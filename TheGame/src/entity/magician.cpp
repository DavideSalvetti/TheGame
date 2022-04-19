#include "magician.h"

#include <QDebug>

#define MAX_MAGICIAN_LIFEPOINTS 6

Magician::Magician(QObject *parent)
    : Character{parent}
{
    lifePoints = MAX_MAGICIAN_LIFEPOINTS;
    attackPoints = 5;
    defPoints = 2;
    moveRange = 1;
    attackRange = 2;
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
    imageSrc = "qrc:/img/wizard.png";
}

Magician::~Magician()
{
    qDebug() << "Magician Destroyed";
}

bool Magician::canMagicAttack() const
{
    return numAttacksAvailable > 0;
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
