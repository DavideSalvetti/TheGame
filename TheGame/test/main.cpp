
#include <QTest>

#include "testgame.h"
#include "testmap.h"
#include "testtile.h"
#include "testcharacter.h"

int main(int argc, char** argv)
{

    /* In this situation, a lambda function is really useful.
     * I declare a function with a name that I can invoke passing different arguments.
     * In this case, the arguments are Test Object, and the function verifies that each test
     * pass */

    int status = 0;
    auto ASSERT_TEST = [&status, argc, argv](QObject* obj) {
        status |= QTest::qExec(obj, argc, argv);
    };

    TestGame testGame;
    TestTile testTile;
    TestCharacter testCharacter;

    ASSERT_TEST(&testGame);
    ASSERT_TEST(&testTile);
    ASSERT_TEST(&testCharacter);

    return status;
}
