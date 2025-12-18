#include "Game.h"
#include <iostream>
#include <algorithm>

namespace dungeon {

Game::Game() {}
Game::Game(const Game&) {}
Game::~Game() {}

void Game::showStats(const Player& player) const {
    std::cout << "HP: " << player.getHealth()
    << " DMG: " << player.getDamage()
    << " DEF: " << player.getDefense() << "\n";
}

void Game::showRoom(const Player& player) const
{
    Room* r = player.getRoom();

    std::cout << "\nYou are in: " << r->getName() << "\n";
    std::cout << r->getDescription() << "\n\n";

    if (r->getEnemy())
    {
        std::cout << "There is an enemy: "
                  << r->getEnemy()->getName() << "!\n";
    }

    if (!r->getItems().empty())
    {
        for (const auto& item : r->getItems())
            std::cout << "There is an item: " << item << "\n";
    }

    if (r->treasure())
        std::cout << "There is the Emerald!!\n";

    std::cout << "\nBeschikbare uitgangen:\n";
    const auto& conns = r->getConnections();
    for (size_t i = 0; i < conns.size(); ++i)
    {
        std::cout << "  [" << i << "] "
                  << conns[i]->getName() << "\n";
    }
}


void Game::takeItems(Player& player) const {
    auto& items = player.getRoom()->accessItems();
    for (const auto& item : items)
        player.addItem(item);
    items.clear();
}

void Game::fight(Player& player) const {
    Enemy* enemy = player.getRoom()->getEnemy();
    if (!enemy) return;

    while (!enemy->isDead() && player.getHealth() > 0) {
        enemy->takeDamage(player.getDamage());
        player.takeDamage(
            std::max(0, enemy->attack() - player.getDefense()));
    }
    player.getRoom()->removeEnemy();
}

void Game::enterRoom(Player& player, Room* next, Room* previous) const {
    player.moveTo(next);
}

void Game::movePlayer(Player& player, int index) const {
    auto& conns = player.getRoom()->getConnections();
    if (index >= 0 && index < (int)conns.size())
        enterRoom(player, conns[index], player.getRoom());
}

} // namespace dungeon
