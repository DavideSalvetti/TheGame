#include "testtile.h"
#include <QtTest>
#include "../src/map/tile.h"

void TestTile::canMoveWhenFree()
{
    QScopedPointer<Tile> tile(new Tile());

    QCOMPARE(tile->canMoveOnTile(), true);
}

void TestTile::canMoveWhenNotSolid()
{
    QScopedPointer<Tile> tile(new Tile());

    QCOMPARE(tile->canMoveOnTile(), true);
}

void TestTile::cannotMoveWhenNotFree()
{
    QScopedPointer<Tile> tile(new Tile());

    tile->setFree(false);
    QCOMPARE(tile->canMoveOnTile(), false);
}

void TestTile::cannotMoveWhenSolid()
{
    QScopedPointer<Tile> tile(new Tile());

    tile->setSolid(true);
    QCOMPARE(tile->canMoveOnTile(), false);
}


