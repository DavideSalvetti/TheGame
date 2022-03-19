#include "testgame.h"

#include <QTest>
#include "../src/game.h"

/*!
 * \brief Verify the correct initialization of the object Game.
 * \details Verify also the correct implementation of the Singleton Pattern,
 * verifying that the object pointed by the two variables is the same in the memory.
 */
void TestGame::initGame()
{
    Game &game = Game::getInstance();

    QCOMPARE(game.getRoundNum(), 1);
    QCOMPARE(game.getRoundPlayer(), 1);

    Game &game_2 = Game::getInstance();

    QVERIFY(&game == &game_2);
}

/*!
 * \brief Verify the correct implementation of the round logic.
 * \details Test the logic for 5 round.
 */
void TestGame::incrementRound()
{
    Game &game = Game::getInstance();


    for (int round = 1; round < 5; round ++) {
        QCOMPARE(game.getRoundNum(), round);

        game.nextPlayer();
        QCOMPARE(game.getRoundPlayer(), 2);

        game.nextPlayer();
        QCOMPARE(game.getRoundPlayer(), 1);
    }

}

