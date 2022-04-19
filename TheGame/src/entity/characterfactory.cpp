#include "characterfactory.h"
#include "swordsman.h"
#include "archer.h"
#include "magician.h"
#include "knight.h"
#include "ninja.h"

#include <QDebug>

CharacterFactory & CharacterFactory::getInstance()
{
    static CharacterFactory instance;
    return instance;
}

CharacterFactory::~CharacterFactory()
{
    qDebug() << "Destroying CharacterFactory!";
}

Character *CharacterFactory::createSwordsman()
{
    return new Swordsman();
}

Character *CharacterFactory::createArcher()
{
    return new Archer();
}

Character *CharacterFactory::createMagician()
{
    return new Magician();
}

Character *CharacterFactory::createWarrior()
{
    return new Knight();
}

Character *CharacterFactory::createNinja()
{
    return new Ninja();
}


CharacterFactory::CharacterFactory()
{
    qDebug() << "Creating CharacterFactory!";
}
