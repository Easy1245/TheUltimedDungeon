#ifndef ENEMY_H
#define ENEMY_H

#include <string>

namespace dungeon {

class Enemy {
protected:
    std::string name;
    int health;

public:
    Enemy();
    Enemy(const std::string& n, int h);
    Enemy(const Enemy& other);
    virtual ~Enemy();

    const std::string& getName() const;
    int getHealth() const;
    bool isDead() const;

    void takeDamage(int dmg = 1);

    virtual int attack() const = 0;
};

}

#endif
