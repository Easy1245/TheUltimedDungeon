#include "dungeon.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>
#include <iostream>
#include <limits>

// globale flag om het spel te stoppen
bool gameRunning = true;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << "⚔️  Welcome, traveler...\n";
    std::cout << "Welcome to *The Ultimate Dungeon*.\n\n";

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
    rooms[2]->items.push_back("Dragon Key");
    rooms[7]->items.push_back("Royal Key");
    rooms[5]->items.push_back("Enchanted Golden Apple");
    rooms[9]->items.push_back("Hyrule Shield");
    rooms[11]->items.push_back("Excaliber");
    rooms[14]->items.push_back("Iron Pickaxe");
    rooms[14]->items.push_back("Echo Crystal");
    rooms[16]->items.push_back("Golden Apple");
    rooms[17]->items.push_back("Rune Stone");
    rooms[18]->items.push_back("Golden Apple");
    rooms[20]->items.push_back("Rusty Key");
    rooms[1]->items.push_back("fernandes bottle");
    rooms[4]->items.push_back("Enchanted Armor");
    rooms[6]->items.push_back("Golden Apple");
    rooms[10]->items.push_back("Golden Apple");

    // --- Monsters ---
    rooms[1]->monster = std::make_unique<Monster>("Dark Spirit", 50);
    rooms[2]->monster = std::make_unique<Monster>("Fire Dragon", 80);
    rooms[3]->monster = std::make_unique<Monster>("Toxic Slime", 35);
    rooms[14]->monster = std::make_unique<Monster>("Echo Ghost", 25);
    rooms[16]->monster = std::make_unique<Monster>("Cursed Miner", 30);
    rooms[17]->monster = std::make_unique<Monster>("Rune Sentinel", 45);
    rooms[18]->monster = std::make_unique<Monster>("Guardian Snake", 55);
    rooms[19]->monster = std::make_unique<Monster>("Haunted Wraith", 40);
    rooms[21]->monster = std::make_unique<Monster>("Slifer The Sky Dragon", 150);
    rooms[21]->hasTreasure = true;

    // --- Player ---
    Player player("Hero", rooms[0].get());

    // --- MAIN GAME LOOP ---
    while (gameRunning)
    {
        showRoom(player);
        std::cout << "\n> ";

        std::string input;

        if (!std::getline(std::cin, input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // trim
        auto start = input.find_first_not_of(" \t\n\r");
        auto end   = input.find_last_not_of(" \t\n\r");

        if (start == std::string::npos) {
            std::cout << "Ongeldige input!\n";
            continue;
        }

        input = input.substr(start, end - start + 1);

        if (input == "q") {
            std::cout << "👋 Je hebt het spel verlaten.\n";
            break;
        }

        if (input == "take") {
            takeItems(player);
            continue;
        }

        if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
            std::cout << "Ongeldige input! Typ een nummer, 'take' of 'q'.\n";
            continue;
        }

        int choice = std::stoi(input);
        movePlayer(player, choice);
    }

    std::cout << "\n🎮 Game gesloten.\n";
    return 0;
}
