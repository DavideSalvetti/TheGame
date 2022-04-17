#include "archer.h"
#include <QDebug>

#define MAX_ARCHER_LIFEPOINTS 10

Archer::Archer(QObject *parent)
    : Character{parent}
{
    lifePoints = MAX_ARCHER_LIFEPOINTS;
    attackPoints = 3;
    defPoints = 1;
    moveRange = 2;
    attackRange = 2;
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
    imageSrc = "qrc:/img/bow.png";
}

Archer::~Archer()
{
    qDebug() << "Archer Destroyed";
}

int Archer::getMaxLifePoints() const
{
    return MAX_ARCHER_LIFEPOINTS;
}

void Archer::resetProperties()
{
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
}
