#include "windows.h"
#include "screen.h"
#include <array>
#include <fstream>
#include <string>
#include "blocklist.h"
#include "grid.h"

void drawGridWindow(Screen& screen, const Grid& grid, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    (void)width;
    (void)height;
    grid.draw(screen, x, y);
}

void drawInfoWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    screen.drawBox(x, y, width, height, " Info ");
    if (width > 4 && height > 2) {
        screen.drawText(x + 2, y + 1, "Status Window");
        screen.drawText(x + 2, y + 2, "Health: 100%");
        screen.drawText(x + 2, y + 3, "Score: 0");
    }
}

void drawLogWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    screen.drawBox(x, y, width, height, " Log ");
    if (width > 4 && height > 2) {
        screen.drawText(x + 2, y + 1, "Event Log");
        screen.drawText(x + 2, y + 2, "- Ready");
        screen.drawText(x + 2, y + 3, "- Waiting...");
    }
}


void drawBlocksWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const std::array<int, 3>& blocks) {
    screen.drawBox(x, y, width, height, " Blocks ");

    for (std::size_t i = 0; i < blocks.size(); ++i) {
        if (blocks[i] == -1 ) {
            continue;
        }
        std::string encodedRef = callblock(blocks[i]);
        int column = 2;
        std::string rowStr = "";
        for (char c : encodedRef) {
            if (c == '#') {
                rowStr += "#";
            } else if (c == '/') {
                screen.drawText(x + 3 + i * 10, y + column, "#");
                column++;
                rowStr = "";
            } else if (c == '.') {
                rowStr += " ";
            }
        }
        screen.drawText(x + 3 + i * 10, y + column, rowStr);
        screen.drawText(x + 5 + i * 10, y + 7, std::to_string(i+1));
    }
}
