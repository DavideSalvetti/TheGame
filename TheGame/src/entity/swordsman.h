#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "character.h"

class Swordsman : public Character
{
public:
    explicit Swordsman(QObject *parent = nullptr);
};

#endif // SWORDSMAN_H