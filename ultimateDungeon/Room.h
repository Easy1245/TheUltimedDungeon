#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <memory>
#include "Enemy.h"

namespace dungeon {

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

    Room();
    Room(int id, const std::string& name, const std::string& desc);
    Room(const Room& other);
    ~Room();

    const std::string& getName() const;
    const std::string& getDescription() const;

    Enemy* getEnemy() const;
    void setEnemy(std::unique_ptr<Enemy> e);
    void removeEnemy();

    void addItem(const std::string& item);
    std::vector<std::string>& accessItems();
    const std::vector<std::string>& getItems() const;

    void connect(Room* other);
    const std::vector<Room*>& getConnections() const;

    bool treasure() const;
    void setTreasure(bool t);
};

} // namespace dungeon

#endif
