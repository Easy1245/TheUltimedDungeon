#ifndef DUNGEONBUILDER_H
#define DUNGEONBUILDER_H

#include <vector>
#include <memory>
#include <string>

#include "Room.h"
#include "Player.h"

namespace dungeon {

class DungeonBuilder {
public:
    Player build(
        const std::string& playerName,
        std::vector<std::unique_ptr<Room>>& rooms
        );
};

} // namespace dungeon

#endif
