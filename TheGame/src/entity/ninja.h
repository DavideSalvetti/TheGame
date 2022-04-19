#ifndef NINJA_H
#define NINJA_H

#include "magician.h"
#include "knight.h"

class Ninja : public Magician, public Knight
{
public:
    explicit Ninja(QObject *parent = nullptr);
    ~Ninja();

    int getMaxLifePoints() const;
    void resetProperties();
};

#endif // NINJA_H
