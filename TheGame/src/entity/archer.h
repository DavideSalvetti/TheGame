#ifndef ARCHER_H
#define ARCHER_H

#include "character.h"

class Archer : public Character
{
public:
    explicit Archer(QObject *parent = nullptr);
};

#endif // ARCHER_H