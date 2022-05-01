#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include "entity.h"

/*!
 * \brief The DynamicEntity class
 * \details The DynamicEntity class is an abstract class.
 * Subclasses of the DynamicEntity class must implement
 * the setX and setY methods. In this way, thery are "dynamic"
 * and they can move on the map.
 */

namespace game {
namespace entity {

class DynamicEntity : public Entity
{
    Q_OBJECT
public:
    explicit DynamicEntity(QObject *parent = nullptr);
    virtual ~DynamicEntity();

    virtual void move(int x, int y) = 0;
    virtual void setX(int x) = 0;
    virtual void setY(int y) = 0;

};

}
}

#endif // DYNAMICENTITY_H
