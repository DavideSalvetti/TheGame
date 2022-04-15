#ifndef CHARACTERSMODEL_H
#define CHARACTERSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "character.h"


class CharactersModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CharactersModel(QObject *parent = nullptr);

    void addCharacter(Character *newCharacter);
    void resetProperties();
    Character *getCharacter(int xPos, int yPos) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool removeRows(int row, int count, const QModelIndex &parent);
    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);


public slots:
    void removeAt(const int x, const int y);

private:
    QList<Character *> characters;

    enum CharacterRole {
        XPosRole = Qt::UserRole + 1,
        YPosRole,
        OwnerRole,
        ImageRole,
        LifePoints
    };
};

#endif // CHARACTERSMODEL_H
