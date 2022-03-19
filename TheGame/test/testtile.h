#ifndef TESTTILE_H
#define TESTTILE_H

#include <QObject>

class TestTile : public QObject
{
    Q_OBJECT
public:
    TestTile(){};

private slots:
    void canMoveWhenFree();
    void canMoveWhenNotSolid();
    void cannotMoveWhenNotFree();
    void cannotMoveWhenSolid();

};

#endif // TESTTILE_H
