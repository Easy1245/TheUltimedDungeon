#include "Enemy.h"

namespace dungeon {

Enemy::Enemy() : name("Unknown Enemy"), health(10) {}

Enemy::Enemy(const std::string& n, int h)
    : name(n), health(h) {}

Enemy::Enemy(const Enemy& other)
    : name(other.name), health(other.health) {}

Enemy::~Enemy() {}

const std::string& Enemy::getName() const {
    return name;
}

int Enemy::getHealth() const {
    return health;
}

bool Enemy::isDead() const {
    return health <= 0;
}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
}

} // namespace dungeon
