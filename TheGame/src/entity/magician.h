#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "character.h"

class Magician : virtual public Character
{
public:
    explicit Magician(QObject *parent = nullptr);
    virtual ~Magician();

    bool canMagicAttack() const;
    virtual int getMaxLifePoints() const;
    virtual void resetProperties();

};

#endif // MAGICIAN_H
