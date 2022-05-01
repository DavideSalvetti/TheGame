#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "character.h"

namespace game {
namespace entity {

class Swordsman : public Character
{
public:
    explicit Swordsman(QObject *parent = nullptr);
    ~Swordsman();

    int getMaxLifePoints() const;
    void resetProperties();
};
}
}

#endif // SWORDSMAN_H
