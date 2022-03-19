#include "characterfactory.h"
#include "swordsaman.h"
#include "archer.h"
#include "magician.h"


CharacterFactory & CharacterFactory::getInstance()
{
    static CharacterFactory instance;
    return instance;
}

Character *CharacterFactory::createSwordsman()
{
    return new Swordsaman();
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
    return new Swordsaman();
}

CharacterFactory::CharacterFactory()
{

}
