#ifndef TESTGAME_H
#define TESTGAME_H

#include <QObject>

class TestGame : public QObject
{
    Q_OBJECT
public:
    TestGame(){};

private slots:
    void initGame();
    void incrementRound();


};

#endif // TESTGAME_H
