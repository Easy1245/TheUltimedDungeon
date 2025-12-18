#ifndef DUNGEONBUILDER_H
#define DUNGEONBUILDER_H

#include <vector>
#include <memory>
#include "Room.h"
#include "Player.h"

namespace dungeon {

class DungeonBuilder
{
public:
    DungeonBuilder() = default;
    Player build(std::vector<std::unique_ptr<Room>>& rooms);
};

} // namespace dungeon

#endif // DUNGEONBUILDER_H
