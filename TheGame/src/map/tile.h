#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QPointer>
#include "../entity/character.h"


class Tile : public QObject
{
    Q_OBJECT
    Q_PROPERTY (Character *character READ getCharacter NOTIFY characterChanged)
    Q_PROPERTY (bool free READ isFree NOTIFY freeChanged)
public:
    explicit Tile(int x, int y, QObject *parent = nullptr);
    ~Tile();

    int getX();
    int getY();
    bool canMoveOnTile();
    bool isFree();
    void setSolid(bool solid);
    void setFree(bool free);
    void addCharacter(Character *character);
    void removeCharacter();
    Character *getCharacter();


signals:
    void characterChanged();
    void freeChanged();


private:
    bool solid {false};
    bool free {false};
    int x {-1};
    int y {-1};

    QPointer<Character> character {nullptr};
};

#endif // TILE_H
