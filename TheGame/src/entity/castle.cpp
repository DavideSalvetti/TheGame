#include "castle.h"
#include <QDebug>

Castle::Castle(int x, int y, QObject *parent)
    : StaticEntity{x, y, parent}
{

}

Castle::~Castle()
{
    qDebug() << "Castle destructor";
}

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

void Castle::reduceNumStars(int itemCreated)
{
    if (itemCreated == 1)
        numStars -= 2;
    else if (itemCreated == 2)
        numStars -= 2;
    else if (itemCreated == 3)
        numStars -= 4;

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
