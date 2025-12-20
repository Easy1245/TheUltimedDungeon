#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <vector>   
#include <memory>   

#include "Player.h"
#include "Room.h"

namespace dungeon {

class SaveManager {
public:
    static bool save(const Player& player,
                     int currentRoomId,
                     const std::vector<std::unique_ptr<Room>>& rooms);

    static bool load(Player& player,
                     int& currentRoomId,
                     std::vector<std::unique_ptr<Room>>& rooms);

    static bool saveExists();
};

} // namespace dungeon

#endif
