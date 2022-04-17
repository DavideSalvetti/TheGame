#ifndef CASTLE_H
#define CASTLE_H

#include "staticentity.h"

class Castle : public StaticEntity
{
    Q_OBJECT
    Q_PROPERTY(QString imageSrc READ getImageSrc CONSTANT)
    Q_PROPERTY(int numStars READ getNumStars NOTIFY numStarsChanged)
public:
    explicit Castle(int x = 0, int y = 0, QObject *parent = nullptr);
    ~Castle();

    virtual void setPlayerOwner(Owner owner);

    void incrementNumStars();
    void reduceNumStars(int itemCreated);

    QString getImageSrc() const;
    int getNumStars() const;

signals:
    void numStarsChanged();

private:
    QString imageSrc = "";
    int numStars = 0;
};

#endif // CASTLE_H
