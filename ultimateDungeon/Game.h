#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <QObject>

namespace dungeon {

class Room;

class Game : public QObject
{
    Q_OBJECT

private slots:
    void autoSave();

private:
    bool running;
    int currentRoomId;
    Player* playerPtr;
    const std::vector<std::unique_ptr<Room>>* roomsPtr;

    void enterRoom(Player& player, Room* next, Room* previous) const;

public:
    explicit Game(QObject* parent = nullptr);
    void run(Player& player,const std::vector<std::unique_ptr<Room>>& rooms);

    void showStats(const Player& player) const;
    void showRoom(const Player& player) const;
    void takeItems(Player& player) const;
    void fight(Player& player) const;
    void movePlayer(Player& player, int index) const;
};

} // namespace dungeon
#endif
