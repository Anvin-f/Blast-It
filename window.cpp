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
    if (width < 5 || height < 5) {
        return;
    }

    std::size_t maxTextWidth = width > 2 ? width - 2 : 0;

    if (blocks[0] >= 0) {
        for (std::size_t i = 0; i < blocks.size(); ++i) {
            
            std::string encodedRef = callblock(blocks[i]);
            int column = 1;
            std::string rowStr = "";
            for (char c : encodedRef) {
                if (c == '#') {
                    rowStr += "#";
                } else if (c == '/') {
                    screen.drawText(x + 2 + i * 6, y + column, "#");
                    column++;
                } else if (c == '.') {
                    rowStr += " ";
                }
            }
            screen.drawText(x + 2 + i * 6, y + column, rowStr);
        }
    } else {
        std::ifstream file("line.txt");
        std::string line;
        std::size_t row = 0;

        while (row < 5 && std::getline(file, line)) {
            if (row + 1 >= height) {
                break;
            }

            if (line.size() > maxTextWidth) {
                line = line.substr(0, maxTextWidth);
            }

            screen.drawText(x + 1, y + 1 + row, line);
            ++row;
        }

        for (; row < 5 && row + 1 < height; ++row) {
            screen.drawText(x + 1, y + 1 + row, std::string());
        }
    }
}
