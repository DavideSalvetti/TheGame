#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "entity.h"

class StaticEntity : public Entity
{
public:
    explicit StaticEntity(int x, int yPos, QObject *parent = nullptr);
    virtual ~StaticEntity();

};

#endif // STATICENTITY_H
