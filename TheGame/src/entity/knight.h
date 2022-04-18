#ifndef KNIGHT_H
#define KNIGHT_H

#include "character.h"

class Knight : public virtual Character
{
public:
    explicit Knight(QObject *parent = nullptr);
    ~Knight();


    int getMaxLifePoints() const;
    void resetProperties();
};

#endif // KNIGHT_H
