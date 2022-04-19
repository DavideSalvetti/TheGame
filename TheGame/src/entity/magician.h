#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "character.h"

class Magician : public virtual Character
{
public:
    explicit Magician(QObject *parent = nullptr);
    virtual ~Magician();

    bool canMagicAttack() const;
    int getMaxLifePoints() const;
    void resetProperties();

};

#endif // MAGICIAN_H
