#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

namespace dungeon {

class Room; // 👈 forward declaration (netjes!)

class Player {
private:
    std::string name;
    Room* currentRoom;

    unsigned char health;
    unsigned char damage;
    unsigned char defense;

public:
    // 🔹 CONSTRUCTORS (altijd bovenaan)
    Player();                                   // 👈 NIEUW
    Player(const std::string& name, Room* startRoom);

    // 🔹 GETTERS / SETTERS
    const std::string& getName() const;
    void setName(const std::string& name);      // 👈 NIEUW

    Room* getRoom() const;
    void moveTo(Room* room);

    unsigned char getHealth() const;
    unsigned char getDamage() const;
    unsigned char getDefense() const;

    void addItem(const std::string& item);
    void takeDamage(unsigned char dmg);

    std::vector<std::string> inventory;
};

} // namespace dungeon

#endif
