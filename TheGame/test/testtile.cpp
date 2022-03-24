#include "testtile.h"
#include <QtTest>
#include "../src/map/tile.h"

void TestTile::canMoveWhenFree()
{
    QScopedPointer<Tile> tile(new Tile(1, 1));

    QCOMPARE(tile->canMoveOnTile(), true);
}

void TestTile::canMoveWhenNotSolid()
{
    QScopedPointer<Tile> tile(new Tile(1, 1));

    QCOMPARE(tile->canMoveOnTile(), true);
}

void TestTile::cannotMoveWhenNotFree()
{
    QScopedPointer<Tile> tile(new Tile(1, 1));

    tile->setFree(false);
    QCOMPARE(tile->canMoveOnTile(), false);
}

void TestTile::cannotMoveWhenSolid()
{
    QScopedPointer<Tile> tile(new Tile(1, 1));

    tile->setSolid(true);
    QCOMPARE(tile->canMoveOnTile(), false);
}


