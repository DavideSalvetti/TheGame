#include "knight.h"
#include <QDebug>

#define MAX_KNIGHT_LIFEPOINTS 15

Knight::Knight(QObject *parent)
    : Character{parent}
{
    lifePoints = MAX_KNIGHT_LIFEPOINTS;
    attackPoints = 2;
    defPoints = 4;
    moveRange = 2;
    attackRange = 1;
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
    imageSrc = "qrc:/img/knight.png";
}

Knight::~Knight()
{
    qDebug() << "Knight Destroyed";
}

void Knight::incrementAttackPoints()
{
    attackPoints++;
    numAttacksAvailable = 0;
    numMovesAvailable = 0;
    emit attackPointsChanged();
}

int Knight::getMaxLifePoints() const
{
    return MAX_KNIGHT_LIFEPOINTS;
}

void Knight::resetProperties()
{
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
}

bool Knight::canIncrementAttackPoints()
{
    return numAttacksAvailable > 0 && numMovesAvailable > 0
            && attackPoints < 10;
}
