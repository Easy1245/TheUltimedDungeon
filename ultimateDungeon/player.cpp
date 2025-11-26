#include "Player.h"

Player::Player(const std::string& n, Room* start)
    : name(n), currentRoom(start), health(100), damage(10), defense(0) {}

void Player::addItem(const std::string& item) {
    inventory.push_back(item);

    if (item == "Golden Apple") {
        health = std::min(health + 35, 100);
        std::cout << "🍎 Golden Apple geneest je tot " << health << " HP\n";
    }
    else if (item == "Hyrule Shield") {
        defense += 10;
        std::cout << "🛡️ Hyrule Shield verhoogt je defense tot " << defense << "\n";
    }
    else if (item == "Iron Pickaxe") {
        damage += 15;
        std::cout << "⚔️ Iron Pickaxe verhoogt je damage tot " << damage << "\n";
    }
    else if (item == "Excaliber") {
        damage += 50;
        std::cout << "⚔️ Excaliber verhoogt je damage tot " << damage << "\n";
    }
    else if (item == "Enchanted Golden Apple") {
        health = std::min(health + 75, 100);
        std::cout << "🍏 Enchanted Golden Apple geneest je tot " << health << " HP\n";
    }
    else if (item == "fernandes bottle") {
        health = std::min(health + 30, 100);
        std::cout << "🥤 fernandes bottle geneest je tot " << health << " HP\n";
    }
    else if (item == "Enchanted Armor") {
        defense += 40;
        std::cout << "🛡️ Enchanted Armor verhoogt je defense tot " << defense << "\n";
    }
}
