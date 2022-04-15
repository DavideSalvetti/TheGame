#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include "entity.h"

class DynamicEntity : public Entity
{
    Q_OBJECT
public:
    explicit DynamicEntity(QObject *parent = nullptr);
    void move(int x, int y);


signals:

};

#endif // DYNAMICENTITY_H
