#ifndef CHARACTER_H
#define CHARACTER_H

#include "dynamicentity.h"

class Character : public DynamicEntity
{
    Q_OBJECT
    Q_PROPERTY(QString imageSrc READ getImageSrc CONSTANT)
    Q_PROPERTY(int lifePoints READ getLifePoints NOTIFY lifePointsChanged)
public:
    explicit Character(QObject *parent = nullptr);

    bool attack(Character *enemy);
    bool canAttack() const;
    bool canMove() const;
    bool canHeal() const;

    void inflictDamage(int damage);

    int getLifePoints() const;
    QString getImageSrc() const;

    void decreaseMovesAvailable();
    void decreaseAttackAvailable();

    int getMoveRange() const;
    int getAttackRange() const;

    void virtual resetProperties() = 0;


signals:
    void lifePointsChanged();
    void characterDestroyed();

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
