#ifndef GAME_H
#define GAME_H

#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    static Game& getInstance();

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
private:
    Game(QObject *parent = nullptr);

};

#endif // GAME_H
