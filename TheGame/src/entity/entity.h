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
    Q_PROPERTY(int xPos READ getX NOTIFY xPosChanged)
    Q_PROPERTY(int yPos READ getY NOTIFY yPosChanged)
public:
    explicit Entity(QObject *parent = nullptr);
    virtual ~Entity();

    virtual void setPlayerOwner(Owner owner);

    Owner getPlayerOwner() const;
    int getX() const;
    int getY() const;

signals:
    void xPosChanged();
    void yPosChanged();

protected:
    int x;
    int y;
    Owner playerOwner;

};

#endif // ENTITY_H
