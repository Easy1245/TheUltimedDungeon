#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
protected:
    std::string name;
    int health;

public:
    Enemy(const std::string& n, int h) : name(n), health(h) {}
    virtual ~Enemy() {}

    std::string getName() const { return name; }
    int getHealth() const { return health; }
    bool isDead() const { return health <= 0; }

    void takeDamage(int dmg) { health -= dmg; }

    virtual int attack() const = 0; // abstract function
};

#endif
