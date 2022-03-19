#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include "entity.h"

class DynamicEntity : public Entity
{
public:
    explicit DynamicEntity(QObject *parent = nullptr);
    void move(int x, int y);
};

#endif // DYNAMICENTITY_H
