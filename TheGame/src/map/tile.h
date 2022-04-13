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
    Q_PROPERTY (bool underAttack READ isUnderAttack NOTIFY underAttackChanged)
    Q_PROPERTY (bool solid READ isSolid CONSTANT)
public:
    explicit Tile(int x = 0, int y = 0, QObject *parent = nullptr);
    ~Tile();

    int getX() const;
    int getY() const;
    bool canMoveOnTile();
    bool isFree() const;
    bool isUnderAttack() const;
    bool isSolid() const;


    void setSolid(bool solid);
    void setFree(bool free);
    void setUnderAttack(bool underAttack);
    void addCharacter(Character *character);
    void removeCharacter();
    Character *getCharacter();


signals:
    void characterChanged();
    void freeChanged();
    void underAttackChanged();

private:
    bool solid {false};
    bool free {false};
    bool underAttack {false};
    int x {-1};
    int y {-1};

    QPointer<Character> character {nullptr};
};

#endif // TILE_H
