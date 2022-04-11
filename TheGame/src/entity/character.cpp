#include "character.h"

#include <QDebug>

/*!
 * \class Character
 * \brief Abstract class that implements method common to every
 * subclass. Specific method of subclasses, like resetProperties(),
 * are pure virtual, so that the subclass must implement it.
 */

Character::Character(QObject *parent)
    : DynamicEntity{parent}
{

}

bool Character::attack(Character *enemy)
{
    if (this == enemy)
        return false;

    if (this->getPlayerOwner() == enemy->getPlayerOwner())
        return false;

    int damage = 1;
    if (this->attackPoints >= enemy->defPoints)
        damage = this->attackPoints;

    enemy->inflictDamage(damage);

    return true;
}

bool Character::canAttack()
{
    return numAttacksAvailable > 0;
}

bool Character::canMove()
{
    return numMovesAvailable > 0;
}

int Character::getLifePoints()
{
    return lifePoints;
}

QString Character::getImageSrc()
{
    return imageSrc;
}

void Character::decreaseMovesAvailable()
{
    if (numMovesAvailable > 0)
        numMovesAvailable--;
}

void Character::decreaseAttackAvailable()
{
    if (numAttacksAvailable > 0)
        numAttacksAvailable--;
}

int Character::getMoveRange() const
{
    return moveRange;
}

int Character::getAttackRange() const
{
    return attackRange;
}

void Character::inflictDamage(int damage)
{
    qDebug() << "Damage:" << damage;
    if (lifePoints - damage <= 0) {
        lifePoints = 0;
        this->deleteLater();
    } else {
        lifePoints -= damage;
        emit lifePointsChanged();
    }

    qDebug() << "LifePoints:" << lifePoints;
}
