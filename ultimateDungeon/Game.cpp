#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

void Game::showStats(const Player& player) const
{
    std::cout << "Hero stats \n"
              << "---------- \n"
              << "Hp: " << player.getHealth() << "\n"
              << "Damage: " << player.getDamage() << "\n"
              << "Defense: " << player.getDefense() << "\n";
}

void Game::showRoom(const Player& player) const
{
    Room* r = player.getRoom();

    std::cout << "\nJe bent in: " << r->getName() << "\n"
              << r->getDescription() << "\n";

    for (auto& item : r->getItems())
        std::cout << "Je ziet een item: " << item << "\n";

    if (r->treasure())
        std::cout << "Je ziet een schatkist!\n";

    std::cout << "Beschikbare uitgangen:\n";
    auto& conns = r->getConnections();
    for (size_t i = 0; i < conns.size(); i++)
        std::cout << "  [" << i << "] " << conns[i]->getName() << "\n";
}

void Game::takeItems(Player& player) const
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
    {
        std::cout << "Je hebt de schat gevonden! Je wint!\n";
        exit(0);
    }
}

void Game::fight(Player& player) const
{
    Enemy* enemy = player.getRoom()->getEnemy();
    if (!enemy) return;

    std::cout << "\nGevecht begonnen met " << enemy->getName() << "!\n";

    while (!enemy->isDead() && player.getHealth() > 0)
    {
        int dmgToEnemy = player.getDamage();
        enemy->takeDamage(dmgToEnemy);

        int dmgToPlayer = std::max(0, enemy->attack() - player.getDefense());
        player.takeDamage(dmgToPlayer);

        std::cout << "Je doet " << dmgToEnemy << " schade!\n";
        std::cout << "Het monster doet " << dmgToPlayer << " schade terug!\n";

        if (player.getHealth() <= 0)
        {
            std::cout << "Je bent gestorven. Game over.\n";
            exit(0);
        }
    }

    std::cout << "Monster verslagen!\n";
    player.getRoom()->removeEnemy();
}

void Game::enterRoom(Player& player, Room* next, Room* previous) const
{
    player.moveTo(next);

    Enemy* enemy = next->getEnemy();
    if (!enemy) return;

    std::cout << "\nJe bent een " << enemy->getName() << " tegengekomen!\n";

    while (enemy && !enemy->isDead())
    {
        std::cout << "Typ 'fight' om te vechten of 'run' om terug te rennen: ";
        std::string input;
        std::getline(std::cin, input);

        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);

        if (input == "fight")
        {
            fight(player);
            break;
        }
        else if (input == "run")
        {
            std::cout << "Je rent terug naar de vorige kamer!\n";
            player.moveTo(previous);
            break;
        }
        else
        {
            std::cout << "Ongeldige input! Typ 'fight' of 'run'.\n";
        }
    }
}

void Game::movePlayer(Player& player, int index) const
{
    auto& conns = player.getRoom()->getConnections();
    if (index < 0 || index >= (int)conns.size()) {
        std::cout << "Ongeldige keuze.\n";
        return;
    }

    Room* previous = player.getRoom();
    Room* next = conns[index];

    enterRoom(player, next, previous);
}
