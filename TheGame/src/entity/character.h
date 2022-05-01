#ifndef CHARACTER_H
#define CHARACTER_H

#include "dynamicentity.h"

namespace game {
namespace entity {

class Character : public DynamicEntity
{
    Q_OBJECT
    Q_PROPERTY(QString imageSrc READ getImageSrc CONSTANT)
    Q_PROPERTY(int lifePoints READ getLifePoints NOTIFY lifePointsChanged)
    Q_PROPERTY(int maxLifePoints READ getMaxLifePoints CONSTANT)
    Q_PROPERTY(int attackPoints READ getAttackPoints NOTIFY attackPointsChanged)
    Q_PROPERTY(int defPoints READ getDefPoints CONSTANT)
public:
    explicit Character(QObject *parent = nullptr);
    virtual ~Character();

    void setPlayerOwner(Owner owner);

    bool attack(Character *enemy);
    void heal();

    bool canAttack() const;
    bool canMove() const;
    bool canHeal() const;

    void setX(int x);
    void setY(int y);
    void move(int x, int y);

    QString getImageSrc() const;
    int getLifePoints() const;
    int getAttackPoints() const;
    int getDefPoints() const;
    int getMoveRange() const;
    int getAttackRange() const;

    void inflictDamage(int damage);

    void decreaseMovesAvailable();
    void decreaseAttackAvailable();

    void virtual resetProperties() = 0;
    int virtual getMaxLifePoints() const = 0;

signals:
    void lifePointsChanged();
    void characterDestroyed(int x, int y);
    void attackPointsChanged();


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

}
}

#endif // CHARACTER_H
