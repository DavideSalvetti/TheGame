#ifndef CHARACTERFACTORYIF_H
#define CHARACTERFACTORYIF_H

#include "character.h"

class CharacterFactoryIF {

public:
    virtual Character * createSwordsman() = 0;
    virtual Character * createArcher() = 0;
    virtual Character * createMagician() = 0;
    virtual Character * createWarrior() = 0;

};

#endif // CHARACTERFACTORYIF_H
