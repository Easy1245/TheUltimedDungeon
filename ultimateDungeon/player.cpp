#include "Player.h"
#include "Room.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>

namespace dungeon {

std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << "HP: "  << static_cast<int>(player.health)
    << " | DMG: " << static_cast<int>(player.damage)
    << " | DEF: " << static_cast<int>(player.defense);
    return os;
}


Player::Player()
    : name("Hero"), currentRoom(nullptr),
    health(100), damage(10), defense(0),
    alive(true), hasTreasure(false) {}

Player::Player(const std::string& n)
    : name(n), currentRoom(nullptr),
      health(100), damage(10), defense(0) {}

Player::Player(const std::string& n, Room* startRoom)
    : name(n), currentRoom(startRoom),
      health(100), damage(10), defense(0) {}

Player::Player(const Player& other)
    : name(other.name),
    currentRoom(other.currentRoom),
    health(other.health),
    damage(other.damage),
    defense(other.defense),
    inventory(other.inventory)
{
}

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

void Player::takeDamage(int dmg)
{
    health = clampValue(health - dmg, 0, 100);
    if (health == 0)
        alive = false;
}

int Player::getHealth() const { return health; }
int Player::getDamage() const { return damage; }
int Player::getDefense() const { return defense; }

void Player::addItem(const std::string& item)
{
    inventory.push_back(item);

    if (item == "Golden Apple")
    {
        health = clampValue(health + 35, 0, 100);
    }
    else if (item == "Enchanted Golden Apple")
    {
        health = clampValue(health + 75, 0, 100);
    }
    else if (item == "Hyrule Shield")
    {
        defense += 10;
    }
    else if (item == "Iron Pickaxe")
    {
        damage += 15;
    }
}

void Player::addItemRaw(const std::string& item)
{
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

bool Player::isAlive() const {
    return alive;
}

bool Player::hasWon() const {
    return hasTreasure;
}

void Player::setAlive(bool value) {
    alive = value;
}

void Player::setHasTreasure(bool value) {
    hasTreasure = value;
}



} // namespace dungeon
