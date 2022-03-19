#ifndef CHARACTERFACTORY_H
#define CHARACTERFACTORY_H

#include "CharacterFactoryIF.h"

class CharacterFactory : public CharacterFactoryIF
{
public:
    static CharacterFactory &getInstance();

    Character * createSwordsman();
    Character * createArcher();
    Character * createMagician();
    Character * createWarrior();

private:
    CharacterFactory();
};

#endif // CHARACTERFACTORY_H
