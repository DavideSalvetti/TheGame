#ifndef CHARACTER_H
#define CHARACTER_H

#include "dynamicentity.h"

class Character : public DynamicEntity
{
    Q_OBJECT
    Q_PROPERTY(QString imageSrc READ getImageSrc CONSTANT)
    Q_PROPERTY(int lifePoints READ getLifePoints NOTIFY lifePointsChanged)
    Q_PROPERTY(int xPos READ getXPos NOTIFY xPosChanged)
    Q_PROPERTY(int yPos READ getYPos NOTIFY yPosChanged)
public:
    explicit Character(QObject *parent = nullptr);

    bool attack(Character *enemy);
    void heal();

    bool canAttack() const;
    bool canMove() const;
    bool canHeal() const;

    void setX(int x);
    void setY(int y);
    int getXPos() const;
    int getYPos() const;

    void inflictDamage(int damage);

    QString getImageSrc() const;
    int getLifePoints() const;
    int getMoveRange() const;
    int getAttackRange() const;

    void decreaseMovesAvailable();
    void decreaseAttackAvailable();

    void virtual resetProperties() = 0;
    int virtual getMaxLifePoints() const = 0;

signals:
    void lifePointsChanged();
    void characterDestroyed(int x, int y);
    void xPosChanged();
    void yPosChanged();

protected:
    int lifePoints;
    int attackPoints;
    int defPoints;
    int moveRange;
    int attackRange;
    int numAttacksAvailable;
    int numMovesAvailable;
    QString imageSrc = "";
};

#endif // CHARACTER_H
