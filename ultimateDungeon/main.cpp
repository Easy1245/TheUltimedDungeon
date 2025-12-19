#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>

#include "Dungeonbuilder.h"
#include "Game.h"
#include "Player.h"
#include "Room.h"

int main()
{
    using namespace dungeon;

    bool gameRunning = true;

    std::cout << "Enter your name, adventurer: ";
    std::string name;
    std::getline(std::cin, name);

    if (name.empty())
        name = "Hero";

    std::vector<std::unique_ptr<Room>> rooms;

    DungeonBuilder builder;
    Player player = builder.build(name, rooms);

    Game game;

    std::cout << "Welcome to the Dungeon, " << player.getName() << "!\n";

    while (gameRunning)
    {
        game.showStats(player);
        game.showRoom(player);

        std::cout << "\n> ";

        std::string input;
        if (!std::getline(std::cin, input))
            continue;

        // trim
        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);

        if (input == "q")
        {
            std::cout << "Je hebt het spel verlaten.\n";
            gameRunning = false;
        }
        else if (input == "take")
        {
            game.takeItems(player);
        }
        else if (!std::all_of(input.begin(), input.end(), ::isdigit))
        {
            std::cout << "Ongeldige input! Typ een nummer, 'take' of 'q'.\n";
        }
        else
        {
            int index = std::stoi(input);
            game.movePlayer(player, index);
        }
    }

    std::cout << "\n🎮 Game gesloten.\n";
    return 0;
}
