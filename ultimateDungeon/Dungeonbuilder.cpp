#include "Dungeonbuilder.h"
#include "Monster.h"

namespace dungeon {

Player DungeonBuilder::build(std::vector<std::unique_ptr<Room>>& rooms) {
    rooms.push_back(std::make_unique<Room>(0, "Start", "Begin"));
    rooms.push_back(std::make_unique<Room>(1, "Cave", "Dark cave"));

    rooms[0]->connect(rooms[1].get());
    rooms[1]->setEnemy(std::unique_ptr<Enemy>(new Monster("Goblin", 30)));


    return Player("Hero", rooms[0].get());
}

} // namespace dungeon
