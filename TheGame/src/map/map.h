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
    void availableTileToMoveOn(Character *character);
    void availableCharacterToAttack(const Character &character);
    bool canAttackSomebody(const Character &character);

    void resetTiles();
    void resetCharactersProperties();
    void moveCharacterToTile(Tile *tile, Character *character);


private slots:
    void characterDestroyed();

signals:
    void winner(Owner winner);


private:
    int width;
    int height;

    /* In this case, I used the parent-child relationship.
     * When parent is deleted (Map), the children will be destroyed (Tile). */
    QVector<QVector<Tile*>> tilesMatrix;
    QList<Tile *> tilesList;

    QVector<Character*> charactersPlayer1;
    QVector<Character*> charactersPlayer2;

    void populateMap();
};

#endif // MAP_H
