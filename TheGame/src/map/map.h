#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "tile.h"

class Map : public QObject
{
    Q_OBJECT
public:
    explicit Map(int width, int height, QObject *parent = nullptr);
    ~Map();

signals:

private:
    int width;
    int height;

    /* In this case, I used the parent-child relationship.
     * When parent is deleted (Map), the children will be destroyed (Tile). */
    QVector<QVector<Tile*>> tilesMatrix;

};

#endif // MAP_H
