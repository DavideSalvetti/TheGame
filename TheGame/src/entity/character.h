#ifndef CHARACTER_H
#define CHARACTER_H

#include "dynamicentity.h"

class Character : public DynamicEntity
{
    Q_OBJECT
    Q_PROPERTY(QString imageSrc READ getImageSrc CONSTANT)
    Q_PROPERTY(int lifePoints READ getLifePoints NOTIFY lifePointsChanged)
public:
    explicit Character(QObject *parent = nullptr);

    bool attack(Character *enemy);
    void inflictDamage(int damage);
    int getLifePoints();
    QString getImageSrc();

signals:
    void lifePointsChanged();

protected:
    int lifePoints;
    int attackPoints;
    int defPoints;
    QString imageSrc = "";



};

#endif // CHARACTER_H
