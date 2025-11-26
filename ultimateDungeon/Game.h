#ifndef GAME_H
#define GAME_H

#include "Player.h"

void showRoom(const Player& player);
void takeItems(Player& player);
void fight(Player& player);
void movePlayer(Player& player, int index);

#endif
