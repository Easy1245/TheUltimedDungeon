#include "dungeon.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

// ------------------------------------------------
// Globale lijst van kamers (ENKEL hier definiëren!)
// ------------------------------------------------
std::vector<std::unique_ptr<Room>> rooms;

// -------------------------
// Monster
// -------------------------
Monster::Monster(const std::string& n, int h)
    : name(n), health(h) {}

// -------------------------
// Room
// -------------------------
Room::Room(int i, const std::string& n, const std::string& d)
    : id(i), name(n), description(d), hasTreasure(false) {}

void Room::connect(Room* other) {
    if (connections.size() < MAX_CONNECTIONS)
        connections.push_back(other);
    if (other->connections.size() < MAX_CONNECTIONS)
        other->connections.push_back(this);
}

// -------------------------
// Player
// -------------------------
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

// -------------------------
// Show room
// -------------------------
void showRoom(const Player& player) {
    Room* r = player.currentRoom;

    std::cout << "\nJe bent in: " << r->name << "\n"
              << r->description << "\n";

    if (r->monster)
        std::cout << "⚔️ Er is een " << r->monster->name
                  << " hier! (Gezondheid: " << r->monster->health << ")\n";

    for (auto& item : r->items)
        std::cout << "🧺 Je ziet een item: " << item << "\n";

    if (r->hasTreasure)
        std::cout << "💰 Je ziet een schatkist!\n";

    std::cout << "Beschikbare uitgangen:\n";
    for (size_t i = 0; i < r->connections.size(); i++) {
        std::cout << "  [" << i << "] " << r->connections[i]->name << "\n";
    }

    std::cout << "Typ een nummer om te bewegen, 'take' om items te pakken, 'q' om te stoppen.\n";
}

// -------------------------
// Take items
// -------------------------
void takeItems(Player& player) {
    Room* r = player.currentRoom;

    if (r->items.empty()) {
        std::cout << "Geen items.\n";
        return;
    }

    for (auto& item : r->items) {
        std::cout << "Je hebt opgepakt: " << item << "\n";
        player.addItem(item);
    }

    r->items.clear();

    // Win condition
    if (r->hasTreasure) {
        std::cout << "🎉 Je hebt de schat gevonden! Je wint!\n";
        exit(0);
    }
}

// -------------------------
// Fight monster
// -------------------------
void fightMonster(Player& player) {
    Monster* m = player.currentRoom->monster.get();
    if (!m) return;

    std::cout << "\n⚔️ Gevecht begonnen met " << m->name << "!\n";

    while (m->health > 0 && player.health > 0) {
        int dmgToMonster = (rand() % 11) + player.damage;
        int dmgToPlayer = (rand() % 16) + 5;
        int mitigated = std::max(dmgToPlayer - player.defense, 0);

        player.health -= mitigated;
        m->health -= dmgToMonster;

        std::cout << "💥 Je doet " << dmgToMonster << " schade!\n";
        std::cout << "👹 Het monster doet " << mitigated << " schade terug!\n";

        if (player.health <= 0) {
            std::cout << "💀 Je bent gestorven. Game over.\n";
            exit(0);
        }
    }

    std::cout << "✅ Monster verslagen!\n";
    player.currentRoom->monster.reset();
}

// -------------------------
// Move player
// -------------------------
void movePlayer(Player& player, int index) {
    if (index < 0 || index >= (int)player.currentRoom->connections.size()) {
        std::cout << "Ongeldige keuze.\n";
        return;
    }

    Room* next = player.currentRoom->connections[index];
    player.currentRoom = next;

    std::cout << "➡️ Je gaat naar: " << next->name << "\n";

    if (next->monster)
        fightMonster(player);
}
