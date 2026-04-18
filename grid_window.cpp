#include "windows.h"
#include "screen.h"
#include "grid.h"

void drawGridWindow(Screen& screen, const Grid& grid, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    (void)width;
    (void)height;
    grid.draw(screen, x, y);
}
