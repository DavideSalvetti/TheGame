#include "command.h"

Command::Command(const QString icon, const QString description, QObject *parent)
    : QObject{parent},
      icon(icon),
      description(description),
      canExecute(false)
{

}

Command::~Command()
{

}

QString Command::getIcon()
{
    return icon;
}

QString Command::getDescription()
{
    return description;
}

bool Command::getCanExecute() const
{
    return canExecute;
}

void Command::setCanExecute(const bool canExecute)
{
    if (this->canExecute == canExecute)
        return;

    this->canExecute = canExecute;
    emit canExecuteChanged();
}
