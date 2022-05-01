#include "swordsman.h"

#include <QDebug>

#define MAX_SWORDSMAN_LIFEPOINTS 10

namespace game {
namespace entity {

Swordsman::Swordsman(QObject *parent)
    : Character{parent}
{
    lifePoints = MAX_SWORDSMAN_LIFEPOINTS;
    attackPoints = 4;
    defPoints = 3;
    moveRange = 2;
    attackRange = 1;
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
    imageSrc = "qrc:/img/swordsman.png";
}

Swordsman::~Swordsman()
{
    qDebug() << "Swordsman Destroyed";
}

int Swordsman::getMaxLifePoints() const
{
    return MAX_SWORDSMAN_LIFEPOINTS;
}

void Swordsman::resetProperties()
{
    numAttacksAvailable = 1;
    numMovesAvailable = 1;
}

}
}
