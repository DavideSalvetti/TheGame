#include "character.h"

#include <QDebug>

Character::Character(QObject *parent)
    : DynamicEntity{parent}
{

}

bool Character::attack(Character *enemy)
{
    if (this == enemy)
        return false;

    int damage = 1;
    if (this->attackPoints >= enemy->defPoints)
        damage = this->attackPoints;

    enemy->inflictDamage(damage);

    return true;
}

int Character::getLifePoints()
{
    return lifePoints;
}

void Character::inflictDamage(int damage)
{
    qDebug() << "Damage:" << damage;
    if (lifePoints - damage <= 0) {
        lifePoints = 0;
        this->deleteLater();
    } else
        lifePoints -= damage;

    qDebug() << "LifePoints:" << lifePoints;
}
