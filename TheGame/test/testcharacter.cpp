#include "testcharacter.h"
#include <QTest>

#include "../src/entity/swordsaman.h"

void TestCharacter::swordsmanAttack()
{
    QScopedPointer<Character> swordsman1(new Swordsaman());
    QScopedPointer<Character> swordsman2(new Swordsaman());

    swordsman1->attack(swordsman2.data());

    QCOMPARE(swordsman2->getLifePoints(), 6);
}
