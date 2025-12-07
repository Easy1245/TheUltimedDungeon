#include "dungeonBuilder.h"
#include "Player.h"

Player DungeonBuilder::build(std::vector<std::unique_ptr<Room>>& rooms)
{
    // --- Kamers ---
    rooms.push_back(std::make_unique<Room>(0, "Lumbrig", "The humble beginning of your adventure."));
    rooms.push_back(std::make_unique<Room>(1, "Darkshrine", "A creepy shrine filled with dark energy."));
    rooms.push_back(std::make_unique<Room>(2, "Dragonden", "A massive cave echoing with the roars of dragons."));
    rooms.push_back(std::make_unique<Room>(3, "Poissendeswap", "A stinking swamp full of poison."));

    // --- Connections ---
    rooms[0]->connect(rooms[1].get());
    rooms[1]->connect(rooms[2].get());
    rooms[2]->connect(rooms[3].get());

    // --- Items ---
    rooms[2]->addItem("Dragon Key");
    rooms[1]->addItem("Enchanted Golden Apple");

    // --- Monsters ---
    rooms[0]->setEnemy(std::make_unique<Monster>("Test Goblin", 10));
    rooms[1]->setEnemy(std::make_unique<Monster>("Dark Spirit", 50));

    // --- Treasure ---
    rooms[3]->setTreasure(true);

    // --- Player (start in kamer 0) ---
    return Player("Hero", rooms[0].get());
}
