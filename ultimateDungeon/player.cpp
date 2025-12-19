#include "Player.h"
#include "Room.h"
#include "Game.h"

namespace dungeon {

Player::Player()
    : name("Unknown"),
    currentRoom(nullptr),
    health(100),
    damage(10),
    defense(5)
{
}

Player::Player(const std::string& n, Room* startRoom)
    : name(n),
    currentRoom(startRoom),
    health(100),
    damage(10),
    defense(5)
{
}

const std::string& Player::getName() const {
    return name;
}

void Player::setName(const std::string& name) {
    this->name = name; // ✔ useful this
}

unsigned char Player::getHealth() const {
    return health;
}

unsigned char Player::getDamage() const {
    return damage;
}

unsigned char Player::getDefense() const {
    return defense;
}

Room* Player::getRoom() const {
    return currentRoom;
}

void Player::moveTo(Room* room) {
    currentRoom = room;
}

void Player::addItem(const std::string& item)
{
    inventory.push_back(item);
}

void Player::takeDamage(unsigned char dmg)
{
    if (dmg >= health)
        health = 0;
    else
        health -= dmg;
}
} // namespace dungeon
