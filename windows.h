#pragma once

#include <array>
#include <cstddef>

class Screen;
class Grid;

void drawEnemyWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height);
void drawPlayerWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height);
void drawGridWindow(Screen& screen, const Grid& grid, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const int table[8][8]);
void drawBlocksWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const int blocks[3]);
