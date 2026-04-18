#pragma once

#include <cstddef>

class Screen;
class Grid;

void drawInfoWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height);
void drawLogWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height);
void drawGridWindow(Screen& screen, const Grid& grid, std::size_t x, std::size_t y, std::size_t width, std::size_t height);
void drawLinesWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height);
