#include "charactersmodel.h"
#include <QDebug>

CharactersModel::CharactersModel(QObject *parent)
    : QAbstractListModel{parent}
{

}
int CharactersModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return characters.size();
}

bool CharactersModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (count <= 0 || row < 0 || (row + count) > rowCount(parent)) return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    while (count > 0) {
        qDebug() << "Removing this " << row;
        delete characters.takeAt(row);
        count--;
    }

    endRemoveRows();

    return true;
}

QHash<int, QByteArray> CharactersModel::roleNames() const
{
    QHash<int, QByteArray> rolenames;

    rolenames[XPosRole] = "xPos";
    rolenames[YPosRole] = "yPos";
    rolenames[OwnerRole] = "owner";
    rolenames[ImageRole] = "imageSrc";
    rolenames[LifePoints] = "lifePoints";


    return rolenames;
}

void CharactersModel::addCharacter(Character* newCharacter)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    characters.append(newCharacter);

    endInsertRows();
}

void CharactersModel::resetProperties()
{
    foreach (Character *character, characters) {
        character->resetProperties();
    }
}

/*!
 * \brief Search for character using xPos and yPos.
 */
Character *CharactersModel::getCharacter(int xPos, int yPos) const
{
    foreach (Character *character, characters) {
        if (character->getX() == xPos && character->getY() == yPos)
            return character;
    }

    return nullptr;
}

void CharactersModel::removeAt(const int x, const int y) {
    qDebug() << "Removing " << x << " and " << y;
    foreach (Character *character, characters) {
        if (character->getX() == x && character->getY() == y) {
            removeRows(characters.indexOf(character), 1, QModelIndex());
        }
    }
}

QVariant CharactersModel::data(const QModelIndex& index, int role) const {
    if (index.isValid()) {
        if (index.row() < rowCount()) {
            switch (role) {
            case XPosRole:
                return characters.at(index.row())->getX();
            case YPosRole:
                return characters.at(index.row())->getY();
            case OwnerRole:
                return characters.at(index.row())->getPlayerOwner();
            case ImageRole:
                return characters.at(index.row())->getImageSrc();
            case LifePoints:
                return characters.at(index.row())->getLifePoints();
            default:
                break;
            }
        }
    }

    return QVariant();
}

bool CharactersModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= characters.count())
        return false;

    Character *character = characters[index.row()];
    if (role == XPosRole) {
        character->setX(value.toInt());
        emit dataChanged(index, index);
        return true;
    }
    else if (role == YPosRole) {
        character->setY(value.toInt());
        emit dataChanged(index, index);
        return true;
    }
    else if (role == LifePoints) {
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

