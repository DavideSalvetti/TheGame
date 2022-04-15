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
    Q_PROPERTY (QQmlListProperty<Character> charactersList READ getCharactersList NOTIFY characterListChanged)

public:
    explicit Map(int width, int height, QObject *parent = nullptr);
    ~Map();

    QQmlListProperty<Tile> getTiles();
    QQmlListProperty<Character> getCharactersList();

    void availableTileToMoveOn(Character *character);
    void availableCharacterToAttack(const Character &character);
    bool canAttackSomebody(const Character &character);
    bool isTileUnderAttack(int x, int y) const;

    void resetTiles();
    void resetCharactersProperties();
    void moveCharacterToTile(Tile *tile, Character *character);
    void resetProperties();



signals:
    void winner(Owner winner);
    void characterListChanged();


private slots:
    void removeCharacter(int x, int y);


private:
    int width;
    int height;

    /* In this case, I used the parent-child relationship.
     * When parent is deleted (Map), the children will be destroyed (Tile). */
    QVector<QVector<Tile*>> tilesMatrix;
    QList<Tile *> tilesList;

    QList<Character*> characters;


    void populateMap();
};

#endif // MAP_H
