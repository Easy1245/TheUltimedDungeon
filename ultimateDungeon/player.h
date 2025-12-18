#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Room.h"
#include "Utils.h"

namespace dungeon {

class Game;

class Player {
    friend class Game;

private:
    std::string name;
    Room* currentRoom;

    unsigned char health;
    unsigned char damage;
    unsigned char defense;

    bool alive;

    std::vector<std::string> inventory;

public:
    Player();
    Player(const std::string& n, Room* start);
    Player(const Player& other);
    ~Player();

    const std::string& getName() const;

    Room* getRoom() const;
    void moveTo(Room* r);

    unsigned char getHealth() const;
    unsigned char getDamage() const;
    unsigned char getDefense() const;

    void takeDamage(unsigned char dmg = 1);

    void addItem(const std::string& item);
};

}

#endif
