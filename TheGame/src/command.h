#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString ui_icon READ getIcon CONSTANT )
    Q_PROPERTY( QString ui_description READ getDescription CONSTANT )
    Q_PROPERTY( bool ui_canExecute READ getCanExecute NOTIFY canExecuteChanged )

public:
    explicit Command(const QString &icon = "", const QString &description = "",
                     QObject *parent = nullptr);
    ~Command();

    QString& getIcon();
    QString& getDescription();
    bool getCanExecute() const;

    void setCanExecute(const bool canExecute);

signals:
    void canExecuteChanged();
    void executed();

private:
    QString icon;
    QString description;
    bool canExecute;

};

#endif // COMMAND_H
