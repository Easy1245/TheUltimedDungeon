#include "Room.h"

Room::Room(int i, const std::string& n, const std::string& d)
    : id(i), name(n), description(d), hasTreasure(false) {}

void Room::connect(Room* other) {
    if (connections.size() < MAX_CONNECTIONS)
        connections.push_back(other);
    if (other->connections.size() < MAX_CONNECTIONS)
        other->connections.push_back(this);
}
