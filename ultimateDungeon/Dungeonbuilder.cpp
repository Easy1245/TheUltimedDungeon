#include "Dungeonbuilder.h"
#include "Monster.h"

namespace dungeon {

Player DungeonBuilder::build(const std::string& playerName, std::vector<std::unique_ptr<Room>>& rooms)
{
    rooms.push_back(std::make_unique<Room>(0, "Lumbrig", "Start of a new journey"));
    rooms.push_back(std::make_unique<Room>(1, "Dark forest", ""));

    rooms[0]->connect(rooms[1].get());

    rooms[1]->setEnemy(std::unique_ptr<Enemy>(new Monster("Goblin", 30)));


    return Player("Hero", rooms[0].get());
}

} // namespace dungeon
