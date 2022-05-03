#include "character.h"

#include <QDebug>

/*!
 * \class Character
 * \brief Abstract class that implements method common to every
 * subclass. Specific method of subclasses, like resetProperties(),
 * are pure virtual, so that the subclass must implement it.
 */

namespace game {
namespace entity {

Character::Character(QObject *parent)
    : DynamicEntity{parent}
{

}

Character::~Character()
{
    qDebug() << "Character Destroyed";
}

void Character::setPlayerOwner(Owner owner)
{
    this->playerOwner = owner;
}

/*!
 * \brief Attack a given \p Character
 * \param enemy The character to attack
 * \return bool
 *      True - the attack has been done correctly
 *      False - the attack hasn't been done correctly
 */
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
/*!
 * \brief If the character has lost some lifepoints, give him some lifepoints
 */
void Character::heal()
{
    if (canHeal()) {
        if (getLifePoints() + 4 > getMaxLifePoints())
            lifePoints = getMaxLifePoints();
        else
            lifePoints += 4;

        emit lifePointsChanged();

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

int Character::getAttackPoints() const
{
    return attackPoints;
}

int Character::getDefPoints() const
{
    return defPoints;
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

/*!
 * \brief Inflict a given damage to this Character
 * \details If the Character remains with 0 lifepoints,
 * emit the signal that communicate that has been destroyed.
 * \param damage The damage to remove from lifepoints
 */
void Character::inflictDamage(int damage)
{
    if (lifePoints - damage <= 0) {
        lifePoints = 0;
        emit characterDestroyed(getX(), getY());
    } else {
        lifePoints -= damage;
        emit lifePointsChanged();
    }
}

void Character::setX(int x)
{
    if (this->x == x) return;

    this->x = x;
    emit xPosChanged();
}

void Character::setY(int y)
{
    if (this->y == y) return;

    this->y = y;
    emit yPosChanged();
}

void Character::move(int x, int y)
{
    setX(x);
    setY(y);
}

}
}


