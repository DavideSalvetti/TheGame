#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QQmlListProperty>
#include "tile.h"
#include "../entity/character.h"
#include "../entity/charactersmodel.h"

class Map : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Tile> tiles READ getTiles CONSTANT)
public:
    explicit Map(int width, int height, QObject *parent = nullptr);
    ~Map();

    QQmlListProperty<Tile> getTiles();
    void availableTileToMoveOn(Character *character);
    void availableCharacterToAttack(const Character &character,
                                    const QList<Character *> &characters);
    bool canAttackSomebody(const Character &character,
                           const QList<Character *> &charactersModel);
    bool isTileUnderAttack(int x, int y) const;

    void resetTiles();
    void resetCharactersProperties();
    void moveCharacterToTile(Tile *tile, Character *character);



signals:
    void winner(Owner winner);


private:
    int width;
    int height;

    /* In this case, I used the parent-child relationship.
     * When parent is deleted (Map), the children will be destroyed (Tile). */
    QVector<QVector<Tile*>> tilesMatrix;
    QList<Tile *> tilesList;
};

#endif // MAP_H
