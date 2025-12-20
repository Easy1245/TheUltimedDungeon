#include "Dungeonbuilder.h"
#include "Monster.h"
#include "Room.h"
#include "Player.h"

namespace dungeon {

Player DungeonBuilder::build(
    const std::string& playerName,
    std::vector<std::unique_ptr<Room>>& rooms
    )
{
    rooms.push_back(std::make_unique<Room>(0, "Lumbrig", "Start of a new journey"));
    rooms.push_back(std::make_unique<Room>(1, "Dark Forest", "Forest filled with darkness"));
    rooms.push_back(std::make_unique<Room>(2, "Dragon Den", "Home of Smaug the dragon"));
    rooms.push_back(std::make_unique<Room>(3, "Olympus", "Home of the Greek gods"));
    rooms.push_back(std::make_unique<Room>(4, "Tilted Towers", "Where we droppen boys"));

    rooms[0]->connect(rooms[1].get());
    rooms[1]->connect(rooms[2].get());
    rooms[0]->connect(rooms[4].get());
    rooms[2]->connect(rooms[3].get());

    rooms[1]->setEnemy(std::make_unique<Monster>("Goblin", 30));
    rooms[3]->setEnemy(std::make_unique<Monster>("Zeus", 200));

    return Player(playerName, rooms[0].get());
}

} // namespace dungeon
