#ifndef TESTCHARACTER_H
#define TESTCHARACTER_H

#include <QObject>

class TestCharacter : public QObject
{
    Q_OBJECT
public:
    TestCharacter(){};

private slots:
    void swordsmanAttack();


};

#endif // TESTCHARACTER_H
