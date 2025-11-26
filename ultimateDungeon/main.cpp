#include "Player.h"
#include "Room.h"
#include "Monster.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <limits>

bool gameRunning = true;
std::vector<std::unique_ptr<Room>> rooms;

int main()
{
    srand((unsigned int)time(nullptr));

    // --- Kamers aanmaken ---
    rooms.push_back(std::make_unique<Room>(0, "Lumbrig", "The humble beginning of your adventure."));
    rooms.push_back(std::make_unique<Room>(1, "Darkshrine", "A creepy shrine filled with dark energy."));
    rooms.push_back(std::make_unique<Room>(2, "Dragonden", "A massive cave echoing with the roars of dragons."));
    rooms.push_back(std::make_unique<Room>(3, "Poissendeswap", "A stinking swamp full of poison."));
    rooms.push_back(std::make_unique<Room>(4, "Legacy Room", "A chamber covered with ancient symbols."));
    rooms.push_back(std::make_unique<Room>(5, "Lake of Hope", "A serene place glowing with hope."));
    rooms.push_back(std::make_unique<Room>(6, "Lava Fissure", "A blazing rift filled with molten lava."));
    rooms.push_back(std::make_unique<Room>(7, "King's Row", "A royal hall with torn banners."));
    rooms.push_back(std::make_unique<Room>(8, "Snowy Plains", "An endless frozen tundra."));
    rooms.push_back(std::make_unique<Room>(9, "Hyrule Castle", "A majestic fortress rising above the land."));
    rooms.push_back(std::make_unique<Room>(10, "Vision Chamber", "A mystical room that reveals unseen paths."));
    rooms.push_back(std::make_unique<Room>(11, "Excalibur Chamber", "A sacred hall holding the legendary sword Excalibur."));
    rooms.push_back(std::make_unique<Room>(12, "Maze of Bones", "A twisted labyrinth made of ancient bones."));
    rooms.push_back(std::make_unique<Room>(13, "Gates of Sorrow", "Massive gates that whisper sorrowful voices."));
    rooms.push_back(std::make_unique<Room>(14, "Cave of Echoes", "A cavern where every sound repeats endlessly."));
    rooms.push_back(std::make_unique<Room>(15, "Howling Chasm", "A deep rift filled with the sound of wailing winds."));
    rooms.push_back(std::make_unique<Room>(16, "The Cursed Mines", "Abandoned tunnels haunted by restless spirits."));
    rooms.push_back(std::make_unique<Room>(17, "Ancient Runes", "A mysterious place covered with glowing runes."));
    rooms.push_back(std::make_unique<Room>(18, "Snake Temple", "A sacred temple devoted to serpents."));
    rooms.push_back(std::make_unique<Room>(19, "Haunted Forest", "A forest filled with eerie whispers and shadows."));
    rooms.push_back(std::make_unique<Room>(20, "Junk Yard", "A pile of forgotten relics and scrap."));
    rooms.push_back(std::make_unique<Room>(21, "Ethernaty, the End", "A place where all journeys come to an end."));

    // --- Connections ---
    rooms[0]->connect(rooms[19].get());
    rooms[0]->connect(rooms[8].get());
    rooms[19]->connect(rooms[15].get());
    rooms[19]->connect(rooms[17].get());
    rooms[17]->connect(rooms[20].get());
    rooms[15]->connect(rooms[20].get());
    rooms[8]->connect(rooms[10].get());
    rooms[8]->connect(rooms[16].get());
    rooms[16]->connect(rooms[14].get());
    rooms[16]->connect(rooms[2].get());
    rooms[14]->connect(rooms[12].get());
    rooms[12]->connect(rooms[3].get());
    rooms[3]->connect(rooms[7].get());
    rooms[2]->connect(rooms[11].get());
    rooms[2]->connect(rooms[6].get());
    rooms[6]->connect(rooms[9].get());
    rooms[6]->connect(rooms[1].get());
    rooms[9]->connect(rooms[18].get());
    rooms[9]->connect(rooms[4].get());
    rooms[1]->connect(rooms[18].get());
    rooms[18]->connect(rooms[13].get());
    rooms[13]->connect(rooms[5].get());
    rooms[13]->connect(rooms[21].get());

    // --- Items ---
    rooms[2]->addItem("Dragon Key");
    rooms[7]->addItem("Royal Key");
    rooms[5]->addItem("Enchanted Golden Apple");
    rooms[9]->addItem("Hyrule Shield");
    rooms[11]->addItem("Excaliber");
    rooms[14]->addItem("Iron Pickaxe");
    rooms[14]->addItem("Echo Crystal");
    rooms[16]->addItem("Golden Apple");
    rooms[17]->addItem("Rune Stone");
    rooms[18]->addItem("Golden Apple");
    rooms[20]->addItem("Rusty Key");
    rooms[1]->addItem("fernandes bottle");
    rooms[4]->addItem("Enchanted Armor");
    rooms[6]->addItem("Golden Apple");
    rooms[10]->addItem("Golden Apple");

    // --- Monsters ---
    rooms[1]->setEnemy(std::make_unique<Monster>("Dark Spirit", 50));
    rooms[2]->setEnemy(std::make_unique<Monster>("Fire Dragon", 80));
    rooms[3]->setEnemy(std::make_unique<Monster>("Toxic Slime", 35));
    rooms[14]->setEnemy(std::make_unique<Monster>("Echo Ghost", 25));
    rooms[16]->setEnemy(std::make_unique<Monster>("Cursed Miner", 30));
    rooms[17]->setEnemy(std::make_unique<Monster>("Rune Sentinel", 45));
    rooms[18]->setEnemy(std::make_unique<Monster>("Guardian Snake", 55));
    rooms[19]->setEnemy(std::make_unique<Monster>("Haunted Wraith", 40));
    rooms[21]->setEnemy(std::make_unique<Monster>("Slifer The Sky Dragon", 150));
    rooms[21]->setTreasure(true);

    // --- Player ---
    Player player("Hero", rooms[0].get());

    // --- Game loop ---
    while (gameRunning)
    {
        showRoom(player);
        std::cout << "\n> ";

        std::string input;
        if (!std::getline(std::cin, input))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);

        if (input == "q") { std::cout << "👋 Je hebt het spel verlaten.\n"; break; }
        if (input == "take") { takeItems(player); continue; }
        if (!std::all_of(input.begin(), input.end(), ::isdigit))
        {
            std::cout << "Ongeldige input! Typ een nummer, 'take' of 'q'.\n"; continue;
        }

        int choice = std::stoi(input);
        movePlayer(player, choice);
    }

    std::cout << "\n🎮 Game gesloten.\n";
    return 0;
}
