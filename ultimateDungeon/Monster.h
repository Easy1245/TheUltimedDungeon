#ifndef MONSTER_H
#define MONSTER_H

#include "Enemy.h"
#include <cstdlib>
#include <string>

namespace dungeon {

class Monster : public Enemy
{
public:
    Monster();
    Monster(const std::string& n, int h);
    Monster(const Monster& other);
    ~Monster() override;

    int attack() const override;
};

} // namespace dungeon

#endif // MONSTER_H
