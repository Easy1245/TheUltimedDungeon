#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>

#include "DungeonBuilder.h"
#include "Game.h"
#include "SaveManager.h"

using namespace dungeon;

int main()
{
    std::cout << "=== DUNGEON GAME ===\n";
    std::cout << "1. New Game\n";
    std::cout << "2. Continue\n";
    std::cout << "Choice: ";

    std::string choice;
    std::getline(std::cin, choice);

    std::vector<std::unique_ptr<Room>> rooms;
    DungeonBuilder builder;
    Game game;
    Player player;

    int currentRoomId = 0;

    // building rooms
    player = builder.build("Hero", rooms);

    if (choice == "2")
    {
        if (!SaveManager::load(player, currentRoomId, rooms))
        {
            std::cout << "No save found. Starting new game.\n";
            choice = "1";
        }
    }

    if (choice == "1")
    {
        std::cout << "Enter your name: ";
        std::string name;
        std::getline(std::cin, name);

        if (name.empty())
            name = "Hero";

        player.setName(name);
        currentRoomId = 0;
    }

    // locate player
    player.moveTo(rooms[currentRoomId].get());

    std::cout << "\nWelcome to the Dungeon, "
              << player.getName() << "!\n";

    std::atomic<bool> autosaveRunning{true};

    std::thread autosaveThread([&]() {
        while (autosaveRunning)
        {
            std::this_thread::sleep_for(std::chrono::seconds(15));
            SaveManager::save(player, currentRoomId, rooms);
            std::cout << "\n[Autosave completed]\n> ";
            std::cout.flush();
        }
    });

    // Game loop
    game.run(player, rooms);

    autosaveRunning = false;
    if (autosaveThread.joinable())
        autosaveThread.join();

    // latest save
    SaveManager::save(player, currentRoomId, rooms);

    std::cout << "\n Game gesloten.\n";
    return 0;
}
