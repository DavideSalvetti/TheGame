#include "castle.h"
#include <QDebug>

namespace game {
namespace entity {

Castle::Castle(int x, int y, QObject *parent)
    : StaticEntity{x, y, parent}
{

}

Castle::~Castle()
{
    qDebug() << "Castle destructor";
}

/*!
 * \brief This method is the implementation of the pure virtual
 * \p setPlayerOwner() inside \p Entity.
 * \details Checks for which player owns the castle to choose the
 *  correct image.
 */
void Castle::setPlayerOwner(Owner owner)
{
    this->playerOwner = owner;
    if (owner == PLAYER_1)
        imageSrc = "qrc:/img/castle.png";
    else
        imageSrc = "qrc:/img/castle_b.png";
}

void Castle::incrementNumStars()
{
    numStars += 2;
    emit numStarsChanged();
}

/*!
 * \brief Based on the item created, it reduces the \p numStars of
 * the castle.
 * \todo It is better to implement an enum for item created, so
 * it is more clear the association between the number of stars and
 * the item.
 * \param itemCreated The item that has been created.
 */
void Castle::reduceNumStars(int itemCreated)
{
    if (itemCreated == 1)
        numStars -= 2;
    else if (itemCreated == 2)
        numStars -= 2;
    else if (itemCreated == 3)
        numStars -= 4;
    else if (itemCreated == 4)
        numStars -= 5;
    else if (itemCreated == 5)
        numStars -= 6;
    else
        qFatal("Must implement new unit.");

    emit numStarsChanged();
}

QString Castle::getImageSrc() const
{
    return imageSrc;
}

int Castle::getNumStars() const
{
    return numStars;
}

}
}
