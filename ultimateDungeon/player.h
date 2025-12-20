#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

namespace dungeon {

class Room;

class Player {
private:
    std::string name;
    Room* currentRoom;
    unsigned char health;
    unsigned char damage;
    unsigned char defense;
    std::vector<std::string> inventory;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);

public:
    Player();
    Player(const std::string& name);
    Player(const std::string& name, Room* startRoom);

    Player(const Player& other);

    const std::string& getName() const;
    void setName(const std::string& n);

    Room* getRoom() const;
    void moveTo(Room* r);

    void addItem(const std::string& item);
    void addItemRaw(const std::string& item);
    void takeDamage(int dmg);

    void setHealth(int health);
    void setDamage(int damage);
    void setDefense(int defense);

    int getHealth() const;
    int getDamage() const;
    int getDefense() const;

    const std::vector<std::string>& getInventory() const;
    void clearInventory();
};

} // namespace dungeon
#endif
