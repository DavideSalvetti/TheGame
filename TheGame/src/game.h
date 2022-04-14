#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "map/map.h"
#include "command.h"
#include "entity/charactersmodel.h"
#include "entity/swordsman.h"

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY (Map *map_ui READ getMap CONSTANT)
    Q_PROPERTY (int roundNum READ getRoundNum NOTIFY roundNumChanged)
    Q_PROPERTY (int roundPlayer READ getRoundPlayer NOTIFY roundPlayerChanged)
    Q_PROPERTY (QQmlListProperty<Command> commandBar READ getCommandBar CONSTANT)
    Q_PROPERTY(CharactersModel* characters READ getCharacters CONSTANT)

public:
    static Game& getInstance();

    void initGame();

    int getRoundNum() const;
    int getRoundPlayer() const;
    Map *getMap() const;
    CharactersModel *getCharacters() const;
    QQmlListProperty<Command> getCommandBar();

    void nextPlayer();

    Q_INVOKABLE void tileClicked(Tile *tile);
    Q_INVOKABLE void characterClicked(int x, int y);
    Q_INVOKABLE void endTurn();


    /* copy-constructor and copy-assigment operator must be
       deleted so that nobody can copy the singleton */
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;



private slots:
    void moveCommandClicked();
    void attackCommandClicked();
    void healCommandClicked();

signals:
    void roundNumChanged();
    void roundPlayerChanged();

private:
    Game(QObject *parent = nullptr);


    enum Action {
        Idle = 0,
        Move,
        Attack
    };

    int mapWidth;
    int mapHeigth;
    int roundNum;
    int roundPlayer;
    Action status {Idle};

    /* I used smart pointers only for learning purposes.
     * It should be fine and easier to use the parent-child
     * relations offered by Qt. */
    QScopedPointer<Map> map;
    CharactersModel *charactersModel {nullptr};

    QPointer<Entity> selectedEntity {nullptr};

    /* List of commands */
    Command *nextTurnCommand {nullptr};
    Command *moveCommand {nullptr};
    Command *attackCommand {nullptr};
    Command *healCommand {nullptr};

    QList<Command*> commandBar;

    void onIdleState(Tile *tile);
    void onMoveState(Tile *tile);
    void onAttackState(Tile *tile);

    void onIdleState(Character *character);
    void onMoveState(Character *character);
    void onAttackState(Character *character);

    void checkPermittedActions();
};

#endif // GAME_H
