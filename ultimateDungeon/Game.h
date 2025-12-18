#ifndef GAME_H
#define GAME_H

#include "Player.h"

namespace dungeon {

class Game {
public:
    Game();
    Game(const Game&);
    ~Game();

    void showStats(const Player& player) const;
    void showRoom(const Player& player) const;
    void takeItems(Player& player) const;
    void fight(Player& player) const;
    void movePlayer(Player& player, int index) const;

private:
    void enterRoom(Player& player, Room* next, Room* previous) const;
};

} // namespace dungeon

#endif
