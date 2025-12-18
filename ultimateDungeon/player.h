#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Room.h"

namespace dungeon {

class Game;

class Player {
private:
    std::string name;
    Room* currentRoom;
    int health;
    int damage;
    int defense;
    std::vector<std::string> inventory;
    unsigned char level;
    unsigned char lives;

public:
    Player();
    Player(const std::string& n, Room* start);
    Player(const Player& other);
    ~Player();

    const std::string& getName() const;
    Room* getRoom() const;
    int getHealth() const;
    int getDamage() const;
    int getDefense() const;

    void setHealth(int h);
    void setDamage(int d);
    void setDefense(int d);

    void moveTo(Room* r);
    void addItem(const std::string& item);
    void takeDamage(int dmg = 1);

    friend class Game;
};

} // namespace dungeon

#endif
