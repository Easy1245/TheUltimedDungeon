#include "Player.h"
#include "Room.h"
#include <algorithm>

namespace dungeon {

Player::Player()
    : name("Hero"), currentRoom(nullptr),
      health(100), damage(10), defense(0) {}

Player::Player(const std::string& n)
    : name(n), currentRoom(nullptr),
      health(100), damage(10), defense(0) {}

Player::Player(const std::string& n, Room* startRoom)
    : name(n), currentRoom(startRoom),
      health(100), damage(10), defense(0) {}

const std::string& Player::getName() const {
    return name;
}

void Player::setName(const std::string& n) {
    name = n;
}

Room* Player::getRoom() const {
    return currentRoom;
}

void Player::moveTo(Room* r) {
    currentRoom = r;
}

void Player::takeDamage(int dmg) {
    health = std::max(0, health - dmg);
}

int Player::getHealth() const { return health; }
int Player::getDamage() const { return damage; }
int Player::getDefense() const { return defense; }

void Player::addItem(const std::string& item) {
    inventory.push_back(item);
}

void Player::setHealth(int health)
{
    this->health = health;
}

void Player::setDamage(int damage)
{
    this->damage = damage;
}

void Player::setDefense(int defense)
{
    this->defense = defense;
}

const std::vector<std::string>& Player::getInventory() const {
    return inventory;
}

void Player::clearInventory() {
    inventory.clear();
}


} // namespace dungeon
