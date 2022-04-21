#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QQmlListProperty>
#include "tile.h"
#include "../entity/character.h"
#include "../entity/castle.h"

class Map : public QObject
{
    Q_OBJECT
    Q_PROPERTY (int mapWidth READ getMapWidth CONSTANT)
    Q_PROPERTY (int mapHeight READ getMapHeight CONSTANT)
    Q_PROPERTY (int tileWidth READ getTileWidth CONSTANT)
    Q_PROPERTY (int tileHeight READ getTileHeight CONSTANT)
    Q_PROPERTY (QQmlListProperty<Tile> tiles READ getTiles CONSTANT)
    Q_PROPERTY (QQmlListProperty<Character> charactersList READ getCharactersList NOTIFY characterListChanged)
    Q_PROPERTY (QQmlListProperty<Castle> castleList READ getCastlesList CONSTANT)
public:
    explicit Map(int width, int height, QObject *parent = nullptr);
    ~Map();

    QQmlListProperty<Tile> getTiles();
    QQmlListProperty<Character> getCharactersList();
    QQmlListProperty<Castle> getCastlesList();
    QList<Character *> getCharacters();
    QList<Castle *> getCastles();

    void availableTileToMoveOn(const Character &character);
    void availableCharacterToAttack(const Character &character);
    bool canAttackSomebody(const Character &character);
    bool isTileUnderAttack(int x, int y) const;

    void resetTiles();
    void moveCharacterToTile(Tile *tile, Character *character);
    void resetProperties();
    void addCharacter(int x, int y, Owner player, int itemSelected);

    int getMapWidth() const;
    int getMapHeight() const;
    int getTileWidth() const;
    int getTileHeight() const;
    bool isCharacterOnTile(int x, int y) const;
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
     * When parent is deleted (Map), the children will be destroyed (Tile).
     * I used QVector (and not QList) because I do more direct access
     * operation than insert/remove. In this case, QVector is more efficient. */
    QVector<QVector<Tile*>> tilesMatrix;

    /* This is needed only to display the tile to the QMLEngine. I bet there
     * is a better approach. */
    QList<Tile *> tilesList;

    QList<Character*> characters;

    QList<Castle*> castles;


    void populateMap();
};

#endif // MAP_H
