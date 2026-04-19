#pragma once

#include <array>
#include <cstddef>
#include "player.h"
#include "combat.h"

class Screen;
class Grid;

void drawEnemyWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const Monster& monster, int difficulty);
void drawPlayerWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const Player& player, int attack_ap = 0, bool use_special = false, int heal_ap = 0, int defend_ap = 0, const std::string& status = "");
void drawGridWindow(Screen& screen, const Grid& grid, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const int table[8][8]);
void drawBlocksWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const int blocks[3]);
