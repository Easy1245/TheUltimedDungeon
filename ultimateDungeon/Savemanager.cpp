#include "SaveManager.h"
#include <fstream>

namespace dungeon {

bool SaveManager::save(const Player& player,
                       int currentRoomId,
                       const std::vector<std::unique_ptr<Room>>& rooms)
{
    std::ofstream file("savegame.txt");
    if (!file)
        return false;

    // ---- Player basis ----
    file << player.getName() << "\n";
    file << player.getHealth() << " "
         << player.getDamage() << " "
         << player.getDefense() << "\n";
    file << currentRoomId << "\n";

    // ---- Inventory ----
    const auto& inventory = player.getInventory();
    file << inventory.size() << "\n";
    for (const auto& item : inventory)
        file << item << "\n";

    // ---- Enemy states per room ----
    file << rooms.size() << "\n";
    for (const auto& room : rooms)
    {
        // 1 = enemy alive, 0 = enemy dead
        file << (room->getEnemy() != nullptr) << "\n";
    }

    return true;
}

bool SaveManager::load(Player& player,
                       int& currentRoomId,
                       std::vector<std::unique_ptr<Room>>& rooms)
{
    std::ifstream file("savegame.txt");
    if (!file)
        return false;

    // ---- Player basis ----
    std::string name;
    int health, damage, defense;

    std::getline(file, name);
    file >> health >> damage >> defense;
    file >> currentRoomId;

    player.setName(name);
    player.setHealth(health);
    player.setDamage(damage);
    player.setDefense(defense);

    // ---- Inventory ----
    size_t inventorySize;
    file >> inventorySize;
    file.ignore();

    player.clearInventory();
    for (size_t i = 0; i < inventorySize; ++i)
    {
        std::string item;
        std::getline(file, item);
        player.addItem(item);
    }

    // ---- Enemy states ----
    size_t roomCount;
    file >> roomCount;

    for (size_t i = 0; i < roomCount && i < rooms.size(); ++i)
    {
        int hasEnemy;
        file >> hasEnemy;

        if (!hasEnemy)
            rooms[i]->removeEnemy();
    }

    return true;
}

bool SaveManager::saveExists()
{
    std::ifstream file("savegame.txt");
    return file.good();
}

} // namespace dungeon
