#include "testcharacter.h"
#include <QTest>

#include "../src/entity/swordsman.h"

using namespace game::entity;

void TestCharacter::swordsmanAttack()
{
    QScopedPointer<Character> swordsman1(new Swordsman());
    QScopedPointer<Character> swordsman2(new Swordsman());

    swordsman1->attack(swordsman2.data());

    QCOMPARE(swordsman2->getLifePoints(), 6);
}
