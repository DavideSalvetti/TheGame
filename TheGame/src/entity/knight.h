#ifndef KNIGHT_H
#define KNIGHT_H

#include "character.h"

class Knight : public virtual Character
{
public:
    explicit Knight(QObject *parent = nullptr);
    virtual ~Knight();


    int getMaxLifePoints() const;
    void resetProperties();

    bool canIncrementAttackPoints();
    void incrementAttackPoints();
};

#endif // KNIGHT_H
