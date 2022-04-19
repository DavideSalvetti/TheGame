#ifndef CHARACTERFACTORY_H
#define CHARACTERFACTORY_H

#include "CharacterFactoryIF.h"

class CharacterFactory : public CharacterFactoryIF
{
public:
    static CharacterFactory &getInstance();
    ~CharacterFactory();

    Character * createSwordsman();
    Character * createArcher();
    Character * createMagician();
    Character * createWarrior();
    Character * createNinja();

    CharacterFactory(CharacterFactory const&) = delete;
    void operator=(CharacterFactory const&) = delete;
private:
    CharacterFactory();
};

#endif // CHARACTERFACTORY_H
