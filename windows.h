#pragma once

#include <array>
#include <cstddef>

class Screen;
class Grid;

void drawInfoWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height);
void drawLogWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height);
void drawGridWindow(Screen& screen, const Grid& grid, std::size_t x, std::size_t y, std::size_t width, std::size_t height);
void drawBlocksWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const std::array<int, 3>& blocks);
