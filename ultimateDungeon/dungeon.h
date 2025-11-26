#ifndef DUNGEON_H
#define DUNGEON_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

// Forward declarations
struct Monster;
struct Room;
struct Player;

// Globale dungeon (wordt alleen gedefinieerd in dungeon.cpp)
extern std::vector<std::unique_ptr<Room>> rooms;

// -------------------------
// Monster
// -------------------------
struct Monster {
    std::string name;
    int health;

    Monster(const std::string& n, int h);
};

// -------------------------
// Room
// -------------------------
struct Room {
    int id;
    std::string name;
    std::string description;
    bool hasTreasure;

    std::unique_ptr<Monster> monster;
    std::vector<std::string> items;
    std::vector<Room*> connections;

    static const int MAX_CONNECTIONS = 4;

    Room(int id, const std::string& name, const std::string& desc);

    void connect(Room* other);
};

// -------------------------
// Player
// -------------------------
struct Player {
    std::string name;
    Room* currentRoom;

    int health;
    int damage;
    int defense;

    std::vector<std::string> inventory;

    Player(const std::string& n, Room* start);

    void addItem(const std::string& item);
};

// -------------------------
// Functies
// -------------------------
void showRoom(const Player& player);
void takeItems(Player& player);
void movePlayer(Player& player, int index);
void fightMonster(Player& player);

#endif
