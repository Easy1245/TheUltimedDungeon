#include "Player.h"
#include <iostream>

namespace dungeon {

Player::Player()
    : name("Unknown"), currentRoom(nullptr),
      health(100), damage(10), defense(0),
      alive(true)
{}

Player::Player(const std::string& n, Room* start)
    : name(n), currentRoom(start),
      health(100), damage(10), defense(0),
      alive(true)
{}

Player::Player(const Player& other)
    : name(other.name),
      currentRoom(other.currentRoom),
      health(other.health),
      damage(other.damage),
      defense(other.defense),
      alive(other.alive)
{}

Player::~Player() {}

const std::string& Player::getName() const {
    return name;
}

Room* Player::getRoom() const {
    return currentRoom;
}

void Player::moveTo(Room* r) {
    this->currentRoom = r; // ✔ this usage
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

void Player::takeDamage(unsigned char dmg) {
    health = clampValue<unsigned char>(
        health > dmg ? health - dmg : 0,
        0, 100
    );
    alive = (health > 0);
}

void Player::addItem(const std::string& item)
{
    inventory.push_back(item);

    if (item == "Enchanted Golden Apple")
        health = clampValue<unsigned char>(health + 40, 0, 100);
}

} // namespace dungeon
