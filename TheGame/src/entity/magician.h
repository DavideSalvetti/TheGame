#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "character.h"

class Magician : public Character
{
public:
    explicit Magician(QObject *parent = nullptr);

    bool magicAttack(Character *enemy);

private:
    int magicPoints;
};

#endif // MAGICIAN_H
