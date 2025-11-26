#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <memory>
#include "Enemy.h"

class Room {
private:
    int id;
    std::string name;
    std::string description;
    bool hasTreasure;

    std::unique_ptr<Enemy> enemy;
    std::vector<std::string> items;
    std::vector<Room*> connections;

public:
    static const int MAX_CONNECTIONS = 4;

    Room(int id, const std::string& name, const std::string& desc);

    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }
    Enemy* getEnemy() const { return enemy.get(); }

    void addItem(const std::string& item) { items.push_back(item); }
    void setEnemy(std::unique_ptr<Enemy> e) { enemy = std::move(e); }
    void removeEnemy() { enemy.reset(); }
    void connect(Room* other);

    std::vector<std::string>& accessItems() { return items; }
    const std::vector<std::string>& getItems() const { return items; }
    bool treasure() const { return hasTreasure; }
    void setTreasure(bool t) { hasTreasure = t; }

    const std::vector<Room*>& getConnections() const { return connections; }
};

#endif
