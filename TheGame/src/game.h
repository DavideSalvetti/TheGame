#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "map/map.h"
#include "command.h"
#include "entity/swordsman.h"
#include "entity/magician.h"
#include "entity/knight.h"

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY (Map *map_ui READ getMap NOTIFY mapHasChanged)
    Q_PROPERTY (int roundNum READ getRoundNum NOTIFY roundNumChanged)
    Q_PROPERTY (int roundPlayer READ getRoundPlayer NOTIFY roundPlayerChanged)
    Q_PROPERTY (QQmlListProperty<Command> commandBar READ getCommandBar CONSTANT)
    Q_PROPERTY (Character *selectedCharacter READ getSelectedCharacter NOTIFY selectedCharacterChanged)

public:
    static Game& getInstance();
    ~Game();

    Q_INVOKABLE void initGame(int width, int heigth);
    Q_INVOKABLE void tileClicked(Tile *tile);
    Q_INVOKABLE void characterClicked(Character *character);
    Q_INVOKABLE void castleClicked(Castle *castle);
    Q_INVOKABLE void endTurn();
    Q_INVOKABLE void addUnit(int itemSelected);

    void nextPlayer();

    int getRoundNum() const;
    int getRoundPlayer() const;
    Map *getMap() const;
    QQmlListProperty<Command> getCommandBar();
    Character *getSelectedCharacter() const;

    /* copy-constructor and copy-assigment operator must be
       deleted so that nobody can copy the singleton. Using
       delete, the default definitions of these operations
       are eliminated. */
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
private slots:
    void moveCommandClicked();
    void attackCommandClicked();
    void magicAttackCommandClicked();
    void incrementAttackCommandClicked();
    void healCommandClicked(); 
    void createCommandClicked();
    void endGame(int winner);

signals:
    void roundNumChanged();
    void roundPlayerChanged();
    void gameFinished(int  winner);
    void mapHasChanged();
    void createUnitClicked(int numStars);
    void selectedCharacterChanged();

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

    Map *map {nullptr};

    /* QPointer is a guarder pointer, so it never becomes a dangling pointer
       because when the reference object is destroyed, it is autmatically
       cleared (set to nullptr). I used it here for learning purposes. */
    QPointer<Entity> selectedEntity {nullptr};

    /* List of commands */
    Command *nextTurnCommand {nullptr};
    Command *moveCommand {nullptr};
    Command *attackCommand {nullptr};
    Command *magicAttackCommand {nullptr};
    Command *healCommand {nullptr};
    Command *createCommand {nullptr};
    Command *incrementAttackCommand {nullptr};

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
