#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "dungeonBuilder.h"
#include "Game.h"
#include "Player.h"
#include "Room.h"

bool gameRunning = true;

int main()
{

    std::vector<std::unique_ptr<Room>> rooms;

    Game game;
    DungeonBuilder builder;

    Player player = builder.build(rooms);

    std::cout << "Welkom in de Dungeon, " << player.getName() << "!\n";

    while (gameRunning)
    {
        game.showStats(player);
        game.showRoom(player);

        std::cout << "\n> ";

        std::string input;
        if (!std::getline(std::cin, input))
        {
            std::cin.clear();
            continue;
        }

        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);

        if (input == "q")
        {
            std::cout << "👋 Je hebt het spel verlaten.\n";
            break;
        }
        else if (input == "take")
        {
            game.takeItems(player);
            continue;
        }
        else if (!std::all_of(input.begin(), input.end(), ::isdigit))
        {
            std::cout << "Ongeldige input! Typ een nummer, 'take' of 'q'.\n";
            continue;
        }

        int index = std::stoi(input);
        game.movePlayer(player, index);
    }

    std::cout << "\n🎮 Game gesloten.\n";
    return 0;
}
