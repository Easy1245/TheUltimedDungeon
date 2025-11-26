#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

void showRoom(const Player& player)
{
    Room* r = player.getRoom();

    std::cout << "\nJe bent in: " << r->getName() << "\n"
              << r->getDescription() << "\n";

    if (r->getEnemy())
        std::cout << "⚔️ Er is een " << r->getEnemy()->getName()
                  << " hier! (Gezondheid: " << r->getEnemy()->getHealth() << ")\n";

    for (auto& item : r->getItems())
        std::cout << "🧺 Je ziet een item: " << item << "\n";

    if (r->treasure())
        std::cout << "💰 Je ziet een schatkist!\n";

    std::cout << "Beschikbare uitgangen:\n";
    auto& conns = r->getConnections();
    for (size_t i = 0; i < conns.size(); i++)
        std::cout << "  [" << i << "] " << conns[i]->getName() << "\n";

    std::cout << "Typ een nummer om te bewegen, 'take' om items te pakken, 'q' om te stoppen.\n";
}

void takeItems(Player& player)
{
    Room* r = player.getRoom();
    if (r->getItems().empty()) { std::cout << "Geen items.\n"; return; }

    auto& items = r->accessItems();
    for (auto& item : items)
    {
        std::cout << "Je hebt opgepakt: " << item << "\n";
        player.addItem(item);
    }
    items.clear();

    if (r->treasure())
    { std::cout << "🎉 Je hebt de schat gevonden! Je wint!\n"; exit(0); }
}

void fight(Player& player)
{
    Enemy* enemy = player.getRoom()->getEnemy();
    if (!enemy) return;

    std::cout << "\n⚔️ Gevecht begonnen met " << enemy->getName() << "!\n";

    while (!enemy->isDead() && player.getHealth() > 0)
    {
        int dmgToEnemy = player.getDamage();
        enemy->takeDamage(dmgToEnemy);

        int dmgToPlayer = std::max(0, enemy->attack() - player.getDefense());
        player.takeDamage(dmgToPlayer);

        std::cout << "💥 Je doet " << dmgToEnemy << " schade!\n";
        std::cout << "👹 Het monster doet " << dmgToPlayer << " schade terug!\n";

        if (player.getHealth() == 0)
        {
            std::cout << "💀 Je bent gestorven. Game over.\n";
            exit(0);
        }
    }

    std::cout << "✅ Monster verslagen!\n";
    player.getRoom()->removeEnemy();
}

void movePlayer(Player& player, int index)
{
    auto& conns = player.getRoom()->getConnections();
    if (index < 0 || index >= (int)conns.size()) { std::cout << "Ongeldige keuze.\n"; return; }

    Room* next = conns[index];
    player.moveTo(next);
    std::cout << "➡️ Je gaat naar: " << next->getName() << "\n";

    if (next->getEnemy()) fight(player);
}
