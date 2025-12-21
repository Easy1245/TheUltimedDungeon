#include "SaveManager.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace dungeon {

bool SaveManager::save(const Player& player, int currentRoomId,
                       const std::vector<std::unique_ptr<Room>>& rooms)
{
    try
    {
        std::ofstream file("savegame.txt");
        if (!file)
            throw std::runtime_error("Failed to open save file");

        file << player.getName() << "\n";
        file << static_cast<int>(player.getHealth()) << "\n";
        file << static_cast<int>(player.getDamage()) << "\n";
        file << static_cast<int>(player.getDefense()) << "\n";
        file << currentRoomId << "\n";

        file << player.getInventory().size() << "\n";
        for (const auto& item : player.getInventory())
            file << item << "\n";

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "[Save error] " << e.what() << "\n";
        return false;
    }
}


bool SaveManager::load(Player& player, int& currentRoomId,
                       const std::vector<std::unique_ptr<Room>>& rooms)
{
    try
    {
        std::ifstream file("savegame.txt");
        if (!file)
            throw std::runtime_error("Save file not found");

        std::string name;
        int health, damage, defense;
        size_t inventorySize;

        std::getline(file, name);
        file >> health >> damage >> defense >> currentRoomId;
        file >> inventorySize;
        file.ignore();

        player.setName(name);
        player.setHealth(health);
        player.setDamage(damage);
        player.setDefense(defense);
        player.clearInventory();

        for (size_t i = 0; i < inventorySize; ++i)
        {
            std::string item;
            std::getline(file, item);
            player.addItemRaw(item); // 🔥 GEEN EFFECT
        }

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "[Load error] " << e.what() << "\n";
        return false;
    }
}


bool SaveManager::saveExists()
{
    std::ifstream file("savegame.txt");
    return file.good();
}

} // namespace dungeon
