#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

enum Owner{
    NONE = 0,
    PLAYER_1,
    PLAYER_2
};

class Entity : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int owner READ getPlayerOwner CONSTANT)
public:
    explicit Entity(QObject *parent = nullptr);
    void setPlayerOwner(Owner owner);
    Owner getPlayerOwner();

    int getX();
    int getY();

protected:
    int x;
    int y;
    Owner playerOwner;

};

#endif // ENTITY_H
