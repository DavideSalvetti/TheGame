#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QQmlListProperty>
#include "tile.h"
#include "../entity/character.h"
#include "../entity/castle.h"

namespace game {
namespace map {

class Map : public QObject
{
    Q_OBJECT
    Q_PROPERTY (int mapWidth READ getMapWidth CONSTANT)
    Q_PROPERTY (int mapHeight READ getMapHeight CONSTANT)
    Q_PROPERTY (int tileWidth READ getTileWidth CONSTANT)
    Q_PROPERTY (int tileHeight READ getTileHeight CONSTANT)
    Q_PROPERTY (QQmlListProperty<game::map::Tile> tiles READ getTiles CONSTANT)
    Q_PROPERTY (QQmlListProperty<game::entity::Character> charactersList READ getCharactersList NOTIFY characterListChanged)
    Q_PROPERTY (QQmlListProperty<game::entity::Castle> castleList READ getCastlesList CONSTANT)
public:
    explicit Map(int width, int height, QObject *parent = nullptr);
    ~Map();

    QQmlListProperty<Tile> getTiles();
    QQmlListProperty<game::entity::Character> getCharactersList();
    QQmlListProperty<game::entity::Castle> getCastlesList();
    QList<game::entity::Character *> getCharacters();
    QList<game::entity::Castle *> getCastles();

    void availableTileToMoveOn(const entity::Character &character);
    void availableCharacterToAttack(const entity::Character &character);
    bool canAttackSomebody(const entity::Character &character);
    bool isTileUnderAttack(int x, int y) const;

    void resetTiles();
    void moveCharacterToTile(Tile *tile, entity::Character *character);
    void resetProperties();
    void addCharacter(int x, int y, entity::Owner player, int itemSelected);

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

    QList<entity::Character*> characters;

    QList<entity::Castle*> castles;


    void populateMap();
};

}
}

#endif // MAP_H
