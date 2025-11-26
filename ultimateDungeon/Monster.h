#ifndef MONSTER_H
#define MONSTER_H

#include "Enemy.h"
#include <cstdlib>

class Monster : public Enemy {
public:
    Monster(const std::string& n, int h) : Enemy(n, h) {}
    int attack() const override { return (rand() % 16) + 5; }
};

#endif
