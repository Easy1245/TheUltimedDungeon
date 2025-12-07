#ifndef DUNGEONBUILDER_H
#define DUNGEONBUILDER_H

#include <vector>
#include <memory>
#include "Room.h"
#include "Player.h"
#include "Monster.h"

class DungeonBuilder
{
public:
    // bouwt kamers, items, monsters, treasure, en returnt de gemaakte speler
    Player build(std::vector<std::unique_ptr<Room>>& rooms);
};

#endif
