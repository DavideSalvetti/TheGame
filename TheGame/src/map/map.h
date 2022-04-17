#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QQmlListProperty>
#include "tile.h"
#include "../entity/character.h"

class Map : public QObject
{
    Q_OBJECT
    Q_PROPERTY (int mapWidth READ getMapWidth CONSTANT)
    Q_PROPERTY (int mapHeight READ getMapHeight CONSTANT)
    Q_PROPERTY (int tileWidth READ getTileWidth CONSTANT)
    Q_PROPERTY (int tileHeight READ getTileHeight CONSTANT)
    Q_PROPERTY (QQmlListProperty<Tile> tiles READ getTiles CONSTANT)
    Q_PROPERTY (QQmlListProperty<Character> charactersList READ getCharactersList NOTIFY characterListChanged)

public:
    explicit Map(int width, int height, QObject *parent = nullptr);
    ~Map();

    QQmlListProperty<Tile> getTiles();
    QQmlListProperty<Character> getCharactersList();
    QList<Character *> getCharacters();

    void availableTileToMoveOn(Character *character);
    void availableCharacterToAttack(const Character &character);
    bool canAttackSomebody(const Character &character);
    bool isTileUnderAttack(int x, int y) const;

    void resetTiles();
    void resetCharactersProperties();
    void moveCharacterToTile(Tile *tile, Character *character);
    void resetProperties();


    int getMapWidth() const;
    int getMapHeight() const;
    int getTileWidth() const;
    int getTileHeight() const;


signals:
    void winner(int winner);
    void characterListChanged();


private slots:
    void removeCharacter(int x, int y);


private:
    int width;
    int height;
    int tileWidth;
    int tileHeight;

    /* In this case, I used the parent-child relationship.
     * When parent is deleted (Map), the children will be destroyed (Tile). */
    QVector<QVector<Tile*>> tilesMatrix;
    QList<Tile *> tilesList;

    QList<Character*> characters;


    void populateMap();
};

#endif // MAP_H
