#ifndef TILE_H
#define TILE_H

#include <QObject>

class Tile : public QObject
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = nullptr);
    ~Tile();

    bool canMoveOnTile();
    void setSolid(bool solid);
    void setFree(bool free);


private:
    bool solid {false};
    bool free {true};

};

#endif // TILE_H
