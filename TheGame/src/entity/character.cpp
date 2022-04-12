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

    this->decreaseAttackAvailable();
    this->decreaseMovesAvailable();

    enemy->inflictDamage(damage);

    return true;
}

void Character::heal()
{
    if (canHeal()) {
        if (getLifePoints() + 3 > getMaxLifePoints())
            lifePoints += getMaxLifePoints();
        else lifePoints += 3;

        numMovesAvailable = 0;
        numAttacksAvailable = 0;
    }
}

bool Character::canAttack() const
{
    return numAttacksAvailable > 0;
}

bool Character::canMove() const
{
    return numMovesAvailable > 0;
}

bool Character::canHeal() const
{
    return numMovesAvailable > 0 && numAttacksAvailable > 0
            && getLifePoints() < getMaxLifePoints();
}

int Character::getLifePoints() const
{
    return lifePoints;
}

QString Character::getImageSrc() const
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
        emit characterDestroyed();
    } else {
        lifePoints -= damage;
        emit lifePointsChanged();
    }

    qDebug() << "LifePoints:" << lifePoints;
}
