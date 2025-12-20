#include "Monster.h"
#include <cstdlib>

namespace dungeon {

Monster::Monster()
    : Enemy("Default Monster", 20) {}

Monster::Monster(const std::string& n, int h)
    : Enemy(n, h) {}

Monster::Monster(const Monster& other)
    : Enemy(other) {}

Monster::~Monster() = default;

int Monster::attack() const
{
    return (std::rand() % 16) + 5;
}

} // namespace dungeon
