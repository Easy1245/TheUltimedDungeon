#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Room.h"

class Player {
private:
    std::string name;
    Room* currentRoom;
    int health;
    int damage;
    int defense;
    std::vector<std::string> inventory;

public:
    Player(const std::string& n, Room* start);

    Room* getRoom() const { return currentRoom; }
    void moveTo(Room* r) { currentRoom = r; }

    void addItem(const std::string& item);

    int getHealth() const { return health; }
    int getDamage() const { return damage; }
    int getDefense() const { return defense; }
    void takeDamage(int dmg) { health -= dmg; }
};

#endif
