#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QQmlListProperty>
#include "tile.h"
#include "../entity/character.h"

class Map : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Tile> tiles READ getTiles CONSTANT)
public:
    explicit Map(int width, int height, QObject *parent = nullptr);
    ~Map();

    QQmlListProperty<Tile> getTiles();

signals:

private:
    int width;
    int height;

    /* In this case, I used the parent-child relationship.
     * When parent is deleted (Map), the children will be destroyed (Tile). */
    QVector<QVector<Tile*>> tilesMatrix;
    QList<Tile *> tilesList;

    QVector<Character*> charactersPlayer1;
    QVector<Character*> charactersPlayer2;

    void populateField();
};

#endif // MAP_H
