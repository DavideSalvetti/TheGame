#include "knight.h"
#include <QDebug>

#define MAX_KNIGHT_LIFEPOINTS 15

Knight::Knight(QObject *parent)
    : Character{parent}
{
    lifePoints = MAX_KNIGHT_LIFEPOINTS;
    attackPoints = 3;
    defPoints = 4;
    moveRange = 2;
    attackRange = 1;
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
    imageSrc = "qrc:/img/knight.png";
}

Knight::~Knight()
{
    qDebug() << "Swordsman Destroyed";
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
