#include "Game.h"
#include "Room.h"
#include "Player.h"
#include "Enemy.h"
#include "SaveManager.h"

#include <iostream>
#include <algorithm>
#include <QTimer>



namespace dungeon {

Game::Game(QObject* parent)
    : QObject(parent),
      running(true),
      currentRoomId(0),
      playerPtr(nullptr),
      roomsPtr(nullptr)
{
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this, &Game::autoSave);
    timer->start(15000);
}

void Game::showStats(const Player& player) const {
    std::cout << player << "\n";
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

void Game::fight(Player& player) const
{
    Enemy* enemy = player.getRoom()->getEnemy();
    if (!enemy)
        return;

    std::cout << "\n Combat started with "
              << enemy->getName() << "!\n\n";

    while (!enemy->isDead() && player.getHealth() > 0)
    {
        // Player attacks
        int playerDamage = player.getDamage();
        enemy->takeDamage(playerDamage);

        std::cout << "You attack "
                  << enemy->getName()
                  << " for " << playerDamage << " damage!\n";
        std::cout << enemy->getName()
                  << " HP: "
                  << std::max(0, enemy->getHealth()) << "\n\n";

        if (enemy->isDead())
            break;

        // Enemy attacks
        int enemyDamage =
            std::max(0, enemy->attack() - player.getDefense());
        player.takeDamage(enemyDamage);

        std::cout << enemy->getName()
                  << " attacks you for "
                  << enemyDamage << " damage!\n";
        std::cout << "Your HP: "
                  << std::max<unsigned char>(0, player.getHealth());

    }

    if (player.getHealth() <= 0)
    {
        std::cout << "You died. Game over.\n";
        std::exit(0);
    }

    std::cout << "You defeated "
              << enemy->getName() << "!\n";

    player.getRoom()->removeEnemy();
}


void Game::enterRoom(Player& player, Room* next, Room* previous) const
{
    player.moveTo(next);

    Enemy* enemy = next->getEnemy();
    if (!enemy)
        return;

    std::cout << "\nThere is an enemy: "
              << enemy->getName() << "!\n";

    while (enemy && !enemy->isDead())
    {
        std::cout << "Type 'fight' to attack or 'run' to go back: ";

        std::string input;
        std::getline(std::cin, input);

        // trim
        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);

        if (input == "fight")
        {
            fight(player);
            break;
        }
        else if (input == "run")
        {
            std::cout << "You run back!\n";
            player.moveTo(previous);
            break;
        }
        else
        {
            std::cout << "Invalid input. Type 'fight' or 'run'.\n";
        }
    }
}


void Game::movePlayer(Player& player, int index) const
{
    Room* current = player.getRoom();

    if (current->getEnemy())
    {
        std::cout << "You cannot leave while an enemy is alive!\n";
        return;
    }

    const auto& conns = current->getConnections();
    if (index < 0 || index >= (int)conns.size())
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    const_cast<Game*>(this)->currentRoomId = conns[index]->getId();

    enterRoom(player, conns[index], current);
}

void Game::run(Player& player, const std::vector<std::unique_ptr<Room>>& rooms)
{
    playerPtr = &player;
    roomsPtr = &rooms;

    auto isNumber = [](const std::string& s) {
        return !s.empty() &&
               std::all_of(s.begin(), s.end(), ::isdigit);
    };

    while (running)
    {
        showStats(player);
        showRoom(player);

        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);

        // trim
        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);

        if (input == "q")
        {
            std::cout << "Je hebt het spel verlaten.\n";
            running = false;   // ✅ member
        }
        else if (input == "take")
        {
            takeItems(player);
        }
        else if (isNumber(input))
        {
            int index = std::stoi(input);
            movePlayer(player, index);
        }
        else
        {
            std::cout << "Ongeldige input! Typ een nummer, 'take' of 'q'.\n";
        }
    }
}

void Game::autoSave()
{
    if (!playerPtr)
        return;

    SaveManager::save(*playerPtr, currentRoomId, *roomsPtr);
    std::cout << "\n[Qt Autosave completed]\n> ";
    std::cout.flush();
}



} // namespace dungeon
