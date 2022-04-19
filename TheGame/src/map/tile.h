#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QPointer>
#include "../entity/character.h"


class Tile : public QObject
{
    Q_OBJECT
    Q_PROPERTY (bool free READ isFree NOTIFY freeChanged)
    Q_PROPERTY (bool underAttack READ isUnderAttack NOTIFY underAttackChanged)
    Q_PROPERTY (bool solid READ isSolid CONSTANT)
public:
    explicit Tile(int x = 0, int y = 0, QObject *parent = nullptr);
    ~Tile();

    int getX() const;
    int getY() const;
    bool canMoveOnTile() const;
    bool isFree() const;
    bool isUnderAttack() const;
    bool isSolid() const;
    bool isEntityPresent() const;


    void setSolid(const bool solid);
    void setFree(const bool free);
    void setUnderAttack(const bool underAttack);
    void setEntityPresent(const bool entityPresent);

signals:
    void freeChanged();
    void underAttackChanged();

private:
    bool solid {false};
    bool free {false};
    bool underAttack {false};
    bool entityPresent {false};
    int x {-1};
    int y {-1};
};

#endif // TILE_H
