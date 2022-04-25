#ifndef KNIGHT_H
#define KNIGHT_H

#include "character.h"

class Knight : virtual public Character
{
public:
    explicit Knight(QObject *parent = nullptr);
    virtual ~Knight();


    virtual int getMaxLifePoints() const;
    virtual void resetProperties();

    bool canIncrementAttackPoints();
    void incrementAttackPoints();
};

#endif // KNIGHT_H
