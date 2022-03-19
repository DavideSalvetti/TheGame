#ifndef CHARACTER_H
#define CHARACTER_H

#include "dynamicentity.h"

class Character : public DynamicEntity
{
public:
    explicit Character(QObject *parent = nullptr);

    bool attack(Character *enemy);
    int getLifePoints();

protected:
    int lifePoints;
    int attackPoints;
    int defPoints;

    void inflictDamage(int damage);

};

#endif // CHARACTER_H
