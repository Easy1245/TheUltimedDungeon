#include "Player.h"

namespace dungeon {

Player::Player()
    : name("Unknown"), currentRoom(nullptr),
      health(100), damage(5), defense(0),
      level(1), lives(3)
{}

Player::Player(const std::string& n, Room* start)
    : name(n), currentRoom(start),
      health(100), damage(10), defense(0),
      level(1), lives(3)
{}

Player::Player(const Player& other)
    : name(other.name), currentRoom(other.currentRoom),
      health(other.health), damage(other.damage),
      defense(other.defense), inventory(other.inventory),
      level(other.level), lives(other.lives)
{}

Player::~Player() {
    std::cout << "[DEBUG] Player destroyed: " << name << std::endl;
}

const std::string& Player::getName() const { return name; }
Room* Player::getRoom() const { return currentRoom; }
int Player::getHealth() const { return health; }
int Player::getDamage() const { return damage; }
int Player::getDefense() const { return defense; }

void Player::setHealth(int h) { health = std::max(0, h); }
void Player::setDamage(int d) { damage = d; }
void Player::setDefense(int d) { defense = d; }

void Player::moveTo(Room* r) { currentRoom = r; }

void Player::takeDamage(int dmg) {
    health = std::max(0, health - dmg);
}

void Player::addItem(const std::string& item) {
    inventory.push_back(item);
}

} // namespace dungeon
