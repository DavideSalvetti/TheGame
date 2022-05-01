#ifndef CHARACTERFACTORY_H
#define CHARACTERFACTORY_H

#include "character.h"

namespace game {
namespace entity {

class CharacterFactory
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

}
}
#endif // CHARACTERFACTORY_H
