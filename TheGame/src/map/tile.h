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
    explicit Tile(QObject *parent = nullptr);
    ~Tile();

    bool canMoveOnTile();
    bool isFree();
    void setSolid(bool solid);
    void setFree(bool free);
    void addCharacter(Character *character);
    Character *getCharacter();

signals:
    void characterChanged();
    void freeChanged();


private:
    bool solid {false};
    bool free {false};

//    QPointer<Character> character {nullptr};
    Character *character {nullptr};
};

#endif // TILE_H
