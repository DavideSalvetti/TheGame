#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QPointer>
#include "../entity/character.h"


class Tile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Character character READ getCharacter NOTIFY characterChanged)
public:
    explicit Tile(QObject *parent = nullptr);
    ~Tile();

    bool canMoveOnTile();
    void setSolid(bool solid);
    void setFree(bool free);
    void addCharacter(Character *character);


private:
    bool solid {false};
    bool free {true};

    QPointer<Character> character {nullptr};
};

#endif // TILE_H
