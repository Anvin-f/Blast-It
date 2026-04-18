#include "windows.h"
#include "screen.h"
#include <array>
#include <fstream>
#include <string>
#include "blocklist.h"
#include "grid.h"
#include "gamedata.h"

void drawGridWindow(Screen& screen, const Grid& grid, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    (void)width;
    (void)height;
    grid.draw(screen, x, y);
}

void drawEnemyWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    screen.drawBox(x, y, width, height, " Enemy ");
    if (width > 4 && height > 2) {
        screen.drawText(x + 2, y + 1, "Name: ");
        screen.drawText(x + 22, y + 1, "Health: ");
        screen.drawText(x + 2, y + 2, "Diff: ");
    }
}

void drawPlayerWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    screen.drawBox(x, y, width, height, " Player Actions ");
    if (width > 4 && height > 2) {
        screen.drawText(x + 2, y + 1, "Health: ");
        screen.drawText(x + 17, y + 1, "Defence: ");
        screen.drawText(x + 32, y + 1, "AP: ");
        screen.drawText(x + 2, y + 3, "1. Attack");
        screen.drawText(x + 2, y + 5, "2. Special");
        screen.drawText(x + 22, y + 3, "3. Heal");
        screen.drawText(x + 22, y + 5, "4. Save AP");
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
