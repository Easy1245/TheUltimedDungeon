#include "Room.h"

namespace dungeon {

Room::Room()
    : id(-1), name("Unknown"), description(""),
        hasTreasure(false), visited(false) {}

Room::Room(int i, const std::string& n, const std::string& d)
    : id(i), name(n), description(d), hasTreasure(false) {}

Room::Room(const Room& other)
    : id(other.id),
      name(other.name),
      description(other.description),
      hasTreasure(other.hasTreasure) {}

Room::~Room() {}

const std::string& Room::getName() const { return name; }
const std::string& Room::getDescription() const { return description; }

Enemy* Room::getEnemy() const { return enemy.get(); }

void Room::setEnemy(std::unique_ptr<Enemy> e) {
    enemy = std::move(e);
}

void Room::removeEnemy() {
    enemy.reset();
}

void Room::addItem(const std::string& item) {
    items.push_back(item);
}

std::vector<std::string>& Room::accessItems() {
    return items;
}

const std::vector<std::string>& Room::getItems() const {
    return items;
}

void Room::connect(Room* other) {
    if (connections.size() < MAX_CONNECTIONS)
        connections.push_back(other);
    if (other && other->connections.size() < MAX_CONNECTIONS)
        other->connections.push_back(this);
}

const std::vector<Room*>& Room::getConnections() const {
    return connections;
}

bool Room::treasure() const { return hasTreasure; }
void Room::setTreasure(bool t) { hasTreasure = t; }
void Room::removeTreasure() { hasTreasure = false; }


bool Room::isVisited() const {return visited; }
void Room::setVisited(bool v) {visited = v; }

}
